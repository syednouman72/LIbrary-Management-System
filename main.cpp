/* NAME: SYED NOUMAN ROLL NUMBER: 21I-1172 SECTION: Q */
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Function for printing a line
void printLine() {
    cout << "\n==========================================\n";
}

// Function for validating input that takes a range
bool inputValidator(string input, int rangeStart, int rangeEnd) {
    bool isInt = true;
    int length = input.length();
    for (int i = 0; i < length; i++) {
        // if there are any characters, return false
        if (!(isdigit(input[i])))
            return false;
    }
    int intForm = stoi(input);
    // if input is not in range, return false
    if (!(intForm >= rangeStart && intForm <= rangeEnd))
        return false;
    return isInt;
}

// Function for validating password input and accesses a user to login
bool userLogin(string* userPasswd, int id, string passInput) {
    if (userPasswd[id] == passInput)
        return true;
    return false;
}

// Function for creating a user
void createUser(int* userId,
                string* userPasswd,
                int* bookBorrowed,
                bool* hasWarning,
                int counter,
                string passInput) {
    userId[counter] = counter;
    userPasswd[counter] = passInput;
    bookBorrowed[counter] = -1;
    hasWarning[counter] = 0;

    ofstream userData;

    // open file
    userData.open("userData.txt", ios::app);

    // write data to file
    userData << userId[counter] << '\n'
             << userPasswd[counter] << '\n'
             << bookBorrowed[counter] << '\n'
             << hasWarning[counter] << '\n';

    // close file
    userData.close();
}

// admin data from main to adminData file
void writeAdminData(string data) {
    ofstream adminData;

    // open file
    adminData.open("adminData.txt");

    // write admin data
    adminData << data << endl;

    // close file
    adminData.close();
}

// read adminData from file, need be
string readAdminData() {
    string line;
    ifstream adminData;

    // open file
    adminData.open("adminData.txt");

    // read admin data
    getline(adminData, line);

    // close file
    adminData.close();
    return line;
}

// Function for reading user data from file, that return user count
int readUserData(int* userId,
                 string* userPsswd,
                 int* bookBorrowed,
                 bool* hasWarning) {
    string line;
    ifstream userData;

    // open file
    userData.open("userData.txt");

    // A user count variable used throughout the program
    int userCount = 0;

    // IF the file exists, store data in the arrays
    if (userData) {
        for (int i = 1; getline(userData, line); i++) {
            userCount++;
            if (i >= 1 && i <= 3) {
                if (i == 1)
                    userId[i - 1] = stoi(line);
                if (i == 2)
                    userPsswd[i - 2] = line;
                if (i == 3)
                    bookBorrowed[i - 3] = stoi(line);
                if (i == 4)
                    hasWarning[i - 4] = stoi(line);
            } else {
                if ((i % 4) == 1)
                    userId[i / 4] = stoi(line);
                if ((i % 4) == 2)
                    userPsswd[i / 4] = line;
                if ((i % 4) == 3) {
                    bookBorrowed[i / 4] = stoi(line);
                    if ((i % 4) == 4) {
                        hasWarning[(i / 4) - 1] = stoi(line);
                    }
                }
            }
        }
        // there is no content in file
    } else
        cout << "No content available to load from file";
    printLine();
    userCount /= 3;
    userData.close();
    return userCount;
}

// Function that writes book data , returns the number of books
int writeBooksData(string bookArr[2][200],
                   bool bookAvailability[],
                   int* bookBorrowed) {
    ifstream bookData;
    string line;

    // the number of books, incrementing after each book is added
    int bookCount = 0;

    // open file
    bookData.open("bookData.txt");
    bool alternatingVar = 0;
    for (int i = 1; getline(bookData, line); i++) {
        bookCount++;
        if (i == 1)
            bookArr[alternatingVar][i - 1] = line;
        else {
            if (i % 2 == 0) {
                bookArr[1][(i / 2) - 1] = line;
            } else {
                bookArr[0][i / 2] = line;
            }
        }
    }

    // CLOSE

    bookData.close();

    for (int i = 0; i < 11; i++) {
        if (bookBorrowed[i] != -1) {
            bookAvailability[bookBorrowed[i]] = 0;
        }
    }
    return bookCount;
}

// if any change happens to the user data, this function will rewrite the file
void updateUserData(int* userId,
                    string* userPsswd,
                    int* bookBorrowed,
                    bool* hasWarning,
                    int userCount) {
    ofstream userData;

    // open file
    userData.open("userData.txt");
    for (int i = 0; i < userCount; i++) {
        userData << userId[i] << '\n'
                 << userPsswd[i] << '\n'
                 << bookBorrowed[i] << '\n'
                 << hasWarning[i] << '\n';
    }

    // close file
    userData.close();
}


// main function
int main() {
    // STATIC ARRAYS
    string bookAuthNames[2][200] = {};
    bool bookAvailability[200] = {};
    int accessRequest[200] = {};

    // SETTING ALL ACCESS REQUESTS TO -1
    for (int i = 0; i < 200; i++)
        accessRequest[i] = -1;

    // MAKING ALL THE BOOKS AVAILABLE
    for (int i = 0; i < 200; i++)
        bookAvailability[i] = 1;

    // ADMIN PASSWORD FROM THE FUNCITON THAT READS FROM FILE
    string adminPass = readAdminData();
    writeAdminData(adminPass);

    // USER COUNT VARIABLES
    int userCount = 0;

    // POINTERS
    int* userIdPtr;
    string* userPasswdPtr;
    int* bookBorrowedPtr;
    bool* hasWarningPtr;

    // DYNAMIC ARRAYS
    userIdPtr = new int[50];
    userPasswdPtr = new string[50];
    bookBorrowedPtr = new int[50];
    hasWarningPtr = new bool[50];

    // SETTING THE ELEMENTS OF REQUIRED ARRAYS TO PRESET VALUES 
    for (int i = 0; i < 50; i++) {
        bookBorrowedPtr[i] = -1;
    }

    for (int i = 0; i < 50; i++) {
        hasWarningPtr[i] = 0;
    }

    // GIVES THE NUMBER OF USERS FROM THE FILE
    userCount =
        readUserData(userIdPtr, userPasswdPtr, bookBorrowedPtr, hasWarningPtr);

    // GIVES THE NUMBER OF BOOKS FROM THE FILE
    int bookCount =
        (writeBooksData(bookAuthNames, bookAvailability, bookBorrowedPtr) / 2);

    // USER INPUT VARIABLES
    string userChoice;
    string passInput;
    int userChoiceInt = 0;

    // START OF USER DISPLAY
    cout << "Welcome to Vector Library, what would you like to do?\n";

    // EXITING CONDITION LOOP
    while (userChoiceInt != -99) {
        printLine();
        cout << "1)User login\n2)Admin Login\n3)Create account\n4)View book "
                "list(-99 TO EXIT)\n";
        cin >> userChoice;
        while (!inputValidator(userChoice, 1, 4)) {
            if (userChoice == "-99")
                break;
            cout << "Please enter the right number!\n";
            cin >> userChoice;
        }
        // CONVERT THE STRING  BACK INTO AN INTEGER
        userChoiceInt = stoi(userChoice);
        switch (userChoiceInt) {
            // USER LOGIN
            case 1: {
                if (!userCount) {
                    cout << "No users exist! Please create an account!\n";
                } else {
                    printLine();
                    int idInput = 0;
                    cout << "Please enter your id: ";
                    cin >> idInput;
                    while (idInput < 0 || idInput > userCount) {
                        cout << "ID does not exist, please try again!";
                        cin >> idInput;
                    }
                    cout << "Please enter your Password: ";
                    cin >> passInput;
                    while (!(userLogin(userPasswdPtr, idInput, passInput))) {
                        cout << "Invalid Password, please try again!";
                        cin >> passInput;
                    }
                    while (userChoiceInt != 3) {
                        printLine();
                        if (hasWarningPtr[idInput]) {
                            cout << "Please return the book you have "
                                    "borrowed!\n";
                        }
                        printLine();
                        cout << "Welcome! What would you like to do?\n1)Borrow "
                                "Book\n2)Change Password\n3)Log Out";
                        cin >> userChoice;
                        while (!inputValidator(userChoice, 1, 3)) {
                            cout << "Please enter the right number!\n";
                            cin >> userChoice;
                        }
                        userChoiceInt = stoi(userChoice);
                        switch (userChoiceInt) {
                            case 1: {
                                bool hasRequested = 0;
                                for (int i = 0; i < bookCount; i++) {
                                    if (accessRequest[i] == idInput)
                                        hasRequested = 1;
                                }
                                if (bookBorrowedPtr[idInput] != -1 ||
                                    hasRequested) {
                                    printLine();
                                    cout << "You have already borrowed or "
                                            "requested a book!\n";
                                    printLine();
                                    break;
                                }
                                printLine();
                                cout << "We have the following books : \n";
                                for (int i = 0; i < bookCount; i++) {
                                    cout << (i + 1) << ") ";
                                    cout << bookAuthNames[0][i] << ", By "
                                         << bookAuthNames[1][i];
                                    cout << endl;
                                }
                                printLine();
                                cout << " Which book do you want to "
                                        "choose?: ";
                                cin >> userChoiceInt;
                                while (userChoiceInt <= 0 ||
                                       userChoiceInt > bookCount) {
                                    cout
                                        << "Please enter a valid input!\nWhich "
                                           "book "
                                           "do you want to choose?: ";
                                    cin >> userChoiceInt;
                                }
                                while (bookAvailability[userChoiceInt] == 0 ||
                                       accessRequest[userChoiceInt] != -1) {
                                    cout << "Book has been borrowed or "
                                            "requested "
                                            "already!\n";
                                    cin >> userChoiceInt;
                                }
                                accessRequest[userChoiceInt - 1] = idInput;
                                cout << "Request Submitted! Please wait till "
                                        "the admin accepts it\n";
                                break;
                            }
                            case 2: {
                                printLine();
                                cout << "Please enter your previous password: ";
                                cin >> passInput;
                                while (passInput != userPasswdPtr[idInput]) {
                                    cout
                                        << "Wrong password! Please try again\n";
                                    cin >> passInput;
                                }
                                cout << "Enter new password: ";
                                cin >> passInput;
                                userPasswdPtr[idInput] = passInput;
                                cout << "Password has been successfully "
                                        "updated!\n";
                                printLine();
                                updateUserData(userIdPtr, userPasswdPtr,
                                               bookBorrowedPtr, hasWarningPtr,
                                               userCount);
                                break;
                            }
                        }
                    }
                    break;
                }
                break;
            }

            // CREATE ACCOUNT
            case 3:
                printLine();
                cout << "\nYour user id is: " << userCount << endl;
                cout << "Please make a password: ";
                cin >> passInput;
                createUser(userIdPtr, userPasswdPtr, bookBorrowedPtr,
                           hasWarningPtr, userCount, passInput);
                cout << "User Created!";
                printLine();
                userCount++;
                break;

            // ADMIN LOGIN
            case 2: {
                cout << "Please enter your password: ";
                cin >> passInput;
                while (passInput != adminPass) {
                    cout << "Wrong Password, Please try again!\n";
                    cin >> passInput;
                }
                userChoiceInt = 0;
                while (userChoiceInt != 6) {
                    cout << "1) Change Password\n2) Stats \n3) Issue "
                            "Warning\n4)Borrow Approval\n5)Book Return\n6)Log "
                            "Out";
                    cin >> userChoice;

                    while (!inputValidator(userChoice, 1, 6)) {
                        cout << "Please enter the right number!\n";
                        cin >> userChoice;
                    }
                    userChoiceInt = stoi(userChoice);
                    switch (userChoiceInt) {
                        case 1:
                            cout << "Please enter previous password: ";
                            cin >> passInput;
                            while (passInput != adminPass) {
                                cout << "Wrong Password, Please try again!\n";
                                cin >> passInput;
                            }
                            cout << "Please enter new Password: ";
                            cin >> adminPass;
                            writeAdminData(adminPass);
                            cout << "Password Updated Successfully!\n";
                            printLine();
                            break;
                        case 3:
                            cout << "Please enter user ID\n";
                            cin >> userChoice;
                            while (!inputValidator(userChoice, 0, userCount)) {
                                cout << "Please enter the right number!\n";
                                cin >> userChoice;
                            }
                            userChoiceInt = stoi(userChoice);
                            if (bookBorrowedPtr[userChoiceInt] > -1) {
                                hasWarningPtr[userChoiceInt] = 1;
                                updateUserData(userIdPtr, userPasswdPtr,
                                               bookBorrowedPtr, hasWarningPtr,
                                               userCount);
                                cout << "Successful!\n";
                            } else
                                cout << "User has not borrowed any book!\n";
                            printLine();
                            break;
                        case 4: {
                            int requestedBook;
                            bool requestFound = false;
                            for (int i = 0; i < bookCount; i++) {
                                if (accessRequest[i] != -1) {
                                    requestedBook = i;
                                    cout << "User " << accessRequest[i]
                                         << " requested " << bookAuthNames[0][i]
                                         << " By " << bookAuthNames[1][i]
                                         << ". Do you want to give access?"
                                         << endl;
                                    requestFound = true;
                                }
                            }
                            if (requestFound) {
                                char continueVar;
                                cin >> continueVar;
                                while (!(continueVar == 'Y' || continueVar == 'N' ||
                                        continueVar == 'y' ||
                                        continueVar == 'n')) {
                                    cout << "Please enter the right choice!\n";
                                    cin >> continueVar;
                                }
                                if (continueVar == 'Y' || continueVar == 'y') {
                                    bookAvailability[requestedBook] = 0;
                                    bookBorrowedPtr[accessRequest[requestedBook]] =
                                        requestedBook;
                                    accessRequest[requestedBook] = -1;
                                    updateUserData(userIdPtr, userPasswdPtr,
                                                bookBorrowedPtr, hasWarningPtr,
                                                userCount);
                                } else {
                                    accessRequest[requestedBook] = -1;
                                }
                            }
                            else {
                                cout << "No requests at the moment!\n";
                            }
                            break;
                        }
                        case 2:
                            printLine();
                            cout << "Books:\nThe library has " << bookCount
                                 << " book at the moment\n";
                            printLine();
                            cout << "Users:\nThe library has " << userCount
                                 << " user at the moment\n";
                            printLine();
                            cout << "Following books are borrowed:\n";
                            for (int i = 0; i < (userCount); i++) {
                                if (bookBorrowedPtr[i] != -1) {
                                    cout << "User " << i << " has borrowed "
                                         << bookAuthNames[0][i] << ", By "
                                         << bookAuthNames[1][i] << endl;
                                }
                            }
                            printLine();
                            break;
                        case 5: {
                            int idInput;
                            cout << "Which user has returned their book? ";
                            cin >> idInput;
                            while (idInput < 0 || idInput >= userCount) {
                                cout << "Invalid User! Please try again!\n";
                                cin >> idInput;
                            }
                            while (bookBorrowedPtr[idInput] == -1) {
                                cout << "User has not borrwed any book!\n";
                                cin >> idInput;
                            }
                            int bookNo = bookBorrowedPtr[idInput];
                            bookAvailability[bookNo] = 1;
                            bookBorrowedPtr[idInput] = -1;
                            updateUserData(userIdPtr, userPasswdPtr,
                                           bookBorrowedPtr, hasWarningPtr,
                                           userCount);
                        }
                    }
                }
                printLine();
                break;
            }
            // VIEW BOOK LIST
            case 4: {
                printLine();
                cout << "We have the following books(We're adding a new book "
                        "everyday!): \n";
                for (int i = 0; i < bookCount; i++) {
                    cout << (i + 1) << ") ";
                    cout << bookAuthNames[0][i] << ", By "
                         << bookAuthNames[1][i];
                    cout << endl;
                }
                printLine();
            }
        }
    }

    delete[] userIdPtr;
    delete[] userPasswdPtr;
    delete[] hasWarningPtr;
    delete[] bookBorrowedPtr;
    return 0;
    // END
}
