#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int copies;

    Book(string t, string a, int c) : title(t), author(a), copies(c) {}
};

struct User {
    string name;
    vector<string> borrowedBooks;

    User(string n) : name(n) {}
};

class LibraryManagementSystem {
private:
    unordered_map<string, Book> books;
    unordered_map<string, User> users;
    priority_queue<pair<int, string>> mostBorrowedBooks;
    unordered_map<string, int> borrowCount;

public:
    void addBook(string title, string author, int copies) {
        books[title] = Book(title, author, copies);
        borrowCount[title] = 0;
        cout << "Book '" << title << "' added successfully.\n";
    }

    void addUser(string name) {
        users[name] = User(name);
        cout << "User '" << name << "' added successfully.\n";
    }

    void borrowBook(string userName, string bookTitle) {
        if (users.find(userName) == users.end()) {
            cout << "User '" << userName << "' does not exist.\n";
            return;
        }
        if (books.find(bookTitle) == books.end()) {
            cout << "Book '" << bookTitle << "' does not exist.\n";
            return;
        }
        if (books[bookTitle].copies <= 0) {
            cout << "Book '" << bookTitle << "' is out of stock.\n";
            return;
        }

        books[bookTitle].copies--;
        users[userName].borrowedBooks.push_back(bookTitle);
        borrowCount[bookTitle]++;
        cout << "Book '" << bookTitle << "' borrowed by '" << userName << "'.\n";
    }

    void returnBook(string userName, string bookTitle) {
        if (users.find(userName) == users.end()) {
            cout << "User '" << userName << "' does not exist.\n";
            return;
        }

        auto &borrowedBooks = users[userName].borrowedBooks;
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookTitle);
        if (it == borrowedBooks.end()) {
            cout << "User '" << userName << "' did not borrow '" << bookTitle << "'.\n";
            return;
        }

        borrowedBooks.erase(it);
        books[bookTitle].copies++;
        cout << "Book '" << bookTitle << "' returned by '" << userName << "'.\n";
    }

    void searchBook(string title) {
        if (books.find(title) == books.end()) {
            cout << "Book '" << title << "' not found.\n";
            return;
        }
        auto &book = books[title];
        cout << "Title: " << book.title << "\nAuthor: " << book.author
             << "\nCopies Available: " << book.copies << "\n";
    }

    void displayMostBorrowedBooks() {
        cout << "Most Borrowed Books:\n";
        vector<pair<int, string>> temp;
        while (!mostBorrowedBooks.empty()) {
            auto top = mostBorrowedBooks.top();
            mostBorrowedBooks.pop();
            cout << "Title: " << top.second << ", Borrowed: " << top.first << " times\n";
            temp.push_back(top);
        }
        for (auto &entry : temp) {
            mostBorrowedBooks.push(entry);
        }
    }

    void updateMostBorrowedBooks() {
        while (!mostBorrowedBooks.empty()) {
            mostBorrowedBooks.pop();
        }
        for (auto &entry : borrowCount) {
            mostBorrowedBooks.push({entry.second, entry.first});
        }
    }
};

int main() {
    LibraryManagementSystem library;

    library.addBook("C++ Programming", "Bjarne Stroustrup", 5);
    library.addBook("Data Structures", "Robert Lafore", 3);
    library.addUser("Alice");
    library.addUser("Bob");

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add User\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. Display Most Borrowed Books\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string title, author, userName;
        int copies;
        switch (choice) {
            case 1:
                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter number of copies: ";
                cin >> copies;
                library.addBook(title, author, copies);
                break;
            case 2:
                cout << "Enter user name: ";
                cin.ignore();
                getline(cin, userName);
                library.addUser(userName);
                break;
            case 3:
                cout << "Enter user name: ";
                cin.ignore();
                getline(cin, userName);
                cout << "Enter book title: ";
                getline(cin, title);
                library.borrowBook(userName, title);
                library.updateMostBorrowedBooks();
                break;
            case 4:
                cout << "Enter user name: ";
                cin.ignore();
                getline(cin, userName);
                cout << "Enter book title: ";
                getline(cin, title);
                library.returnBook(userName, title);
                break;
            case 5:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                library.searchBook(title);
                break;
            case 6:
                library.displayMostBorrowedBooks();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
