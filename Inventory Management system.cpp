#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>  

using namespace std;

class Medicine {
public:
    int* prices;
    string* names;
    int* stock;
    int n;



//    ~Medicine() {
//        delete[] prices;
//        delete[] names;
//        delete[] stock;
//    }
};

class Supplier : public Medicine {
public:
    void greet() {
        cout << endl;
        cout << "ENTER NUMBER OF MEDICINES YOU ARE SUPPLYING: ";
        cin >> n;

        prices = new int[n];
        names = new string[n];
        stock = new int[n];
    }

    void inputStock() {
        cout << "Enter details for " << n << " medicines:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "Enter name for medicine " << i + 1 << ": ";
            cin >> ws; // Clear leading whitespace
            getline(cin, names[i]);
            cout << "Enter price for " << names[i] << ": ";
            cin >> prices[i];
            cout << "Enter stock for " << names[i] << ": ";
            cin >> stock[i];
        }
    }

    void display() const {
        if (n == 0) {
            cout << "No medicines available." << endl;
            return;
        }
        cout << left << setw(10) << "Sr no." << left << setw(35) << "Medicine" << left << setw(10) << "Price" << left << setw(10) << "Stock" << endl;
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << left << setw(10) << i + 1 << left << setw(35) << names[i] << left << setw(10) << prices[i] << left << setw(10) << stock[i] << endl;
        }
    }

    void addMoreMedicines() {
        int additional;
        cout << "Enter number of additional medicines you want to add: ";
        cin >> additional;

        int new_size = n + additional;

        int* new_prices = new int[new_size];
        string* new_names = new string[new_size];
        int* new_stock = new int[new_size];

        for (int i = 0; i < n; ++i) {
            new_prices[i] = prices[i];
            new_names[i] = names[i];
            new_stock[i] = stock[i];
        }

//        delete[] prices;
//        delete[] names;
//        delete[] stock;

        prices = new_prices;
        names = new_names;
        stock = new_stock;

        for (int i = n; i < new_size; ++i) {
            cout << "Enter name for medicine " << i + 1 << ": ";
            cin >> ws;
            getline(cin, names[i]);
            cout << "Enter price for " << names[i] << ": ";
            cin >> prices[i];
            cout << "Enter stock for " << names[i] << ": ";
            cin >> stock[i];
        }

        n = new_size;
    }

    void updateStock(int index, int additionalStock, int newPrice) {
        if (index >= 0 && index < n) {
            stock[index] += additionalStock;
            prices[index] = newPrice;
        } else {
            cout << "Invalid index." << endl;
        }
    }
};

class Buyer : public Supplier {
protected:
    int sr;
    int* a;
    int* b;

public:


    ~Buyer() {
        delete[] a;
        delete[] b;
    }

      void buy() {
        while (true) {
            cout << "-----------------HI CUSTOMER WELCOME TO LIFE PHARMACY----------------------" << endl;
            cout << "FOLLOWING IS OUR AVAILABLE MEDICINES LIST" << endl;
            display();
            cout << endl;
            cout << "ENTER THE NUMBER OF MEDICINES YOU WANT TO BUY: ";
            cin >> sr;
            a = new int[sr];
            b = new int[sr];

            bool validPurchase = true;

            for (int i = 0; i < sr; i++) {
                cout << "ENTER SERIAL NO. OF MEDICINES WHICH YOU WANT TO BUY: ";
                cin >> a[i];
                a[i]--;
                if (a[i] < 0 || a[i] >= n) {
                    cout << "Invalid serial number." << endl;
                    validPurchase = false;
                    break;
                }
                cout << "ENTER QUANTITY FOR MEDICINE " << names[a[i]] << ": ";
                cin >> b[i];
                if (b[i] > stock[a[i]]) {
                    cout << "-----------------OUT OF STOCK-------------------" << endl;
                    validPurchase = false;
                    break;
                } else {
                    stock[a[i]] -= b[i];
                }
            }

            if (validPurchase) {
                break;
            } else {
                cout << "Please try your purchase again." << endl;
            }
        }
    }

    void show() const {
        if (sr == 0) {
            cout << "No medicines bought." << endl;
            return;
        }

        double totalBill = 0;
        cout << endl << "FOLLOWING IS THE LIST OF MEDICINES YOU BOUGHT" << endl;
        cout << left << setw(10) << "Sr no" << left << setw(35) << "Medicine" << left << setw(10) << "Price" << left << setw(20) << "Quantity" << endl;
        for (int i = 0; i < sr; i++) {
            int cost = prices[a[i]] * b[i];
            totalBill += cost;
            cout << left << setw(10) << a[i] + 1 << left << setw(35) << names[a[i]] << left << setw(10) << cost << left << setw(20) << b[i] << endl;
        }

        if (sr > 4) {
            totalBill *= 0.7; 
        }

        cout << endl << "Total Bill: " << totalBill << " (Discount applied if more than 4 items)" << endl;
    }

    void updatedStock() const {
        cout << endl << "FOLLOWING IS THE UPDATED STOCK LEFT AFTER PURCHASES" << endl;
        display();
    }
};

int registerUser() {
    string name;
    int password;

    ofstream outFile("user_data.txt");
    if (!outFile) {
        cout << "Unable to open file for registration." << endl;
        return 0;
    }

    cout << "TO REGISTER ENTER YOUR NAME: ";
    cin >> ws;
    getline(cin, name);
    cout << "PLACE A STRONG PASSWORD: ";
    cin >> password;

    outFile << name << endl;
    outFile << password << endl;

    outFile.close();
    return 1;
}

int loginUser() {
    string registeredName, enteredName;
    int registeredPassword, enteredPassword;

    ifstream inFile("user_data.txt");
    if (!inFile) {
        cout << "Unable to open file for login." << endl;
        return 0;
    }

    cout << "ENTER YOUR NAME WITH WHICH YOU ARE REGISTERED: ";
    cin >> ws;
    getline(cin, enteredName);
    cout << "ENTER YOUR SECURE PASSWORD: ";
    cin >> enteredPassword;

    getline(inFile, registeredName);
    inFile >> registeredPassword;

    inFile.close();

    return (registeredName == enteredName && registeredPassword == enteredPassword) ? 1 : 0;
}

int main() {
    Supplier s1;
    Buyer b1;
    int isRegistered = 0;

    while (true) {
        cout << "-------------------------------HI USER -----------------------------------" << endl;
        cout << "-------------------IF YOU WANT TO SUPPLY MEDICINE PRESS 1-----------------" << endl;
        cout << "---------------------IF YOU WANT TO BUY MEDICINE PRESS 2------------------" << endl;
        cout << "-----------------IF YOU WANT TO UPDATE MEDICINE LIST ENTER 3--------------" << endl;
        cout << "-----------IF YOU WANT TO ADD MEDICINE TO EXISTING STOCK ENTER 4----------" << endl;

        int option;
        cin >> option;
        char backOption;

        if (option == 1) {
            int subOption;
            cout << "IF YOU ARE NOT REGISTERED FIRST REGISTER YOURSELF. TO REGISTER PRESS 1." << endl;
            cout << "IF YOU ARE REGISTERED PRESS 2: ";
            cin >> subOption;

            if (subOption == 1) {
                isRegistered = registerUser();
            } else if (subOption == 2) {
                isRegistered = loginUser();
            }

            if (isRegistered == 0) {
                cout << "Registration/Login failed. Try again." << endl;
                continue;
            }

            s1.greet();
            s1.inputStock();
            s1.display();

            cout << "IF YOU WANT TO MOVE TO MAIN INTERFACE ENTER Y: ";
            cin >> backOption;
            if (backOption == 'Y' || backOption == 'y') {
                continue;
            }
        } else if (option == 2) {
         b1.prices = s1.prices;
            b1.names = s1.names;
            b1.stock = s1.stock;
            b1.n = s1.n;
            b1.buy();
            b1.show();
            b1.updatedStock();

            cout << "IF YOU WANT TO MOVE TO MAIN INTERFACE ENTER Y: ";
            cin >> backOption;
            if (backOption == 'Y' || backOption == 'y') {
                continue;
            }
        } else if (option == 3) {
            int index, additionalStock, newPrice;
            cout << "Enter index of medicine to update: ";
            cin >> index;
            cout << "Enter additional stock: ";
            cin >> additionalStock;
            cout << "Enter new price: ";
            cin >> newPrice;
            s1.updateStock(index - 1, additionalStock, newPrice);
            s1.display();

            cout << "IF YOU WANT TO MOVE TO MAIN INTERFACE ENTER Y: ";
            cin >> backOption;
            if (backOption == 'Y' || backOption == 'y') {
                continue;
            }
        } else if (option == 4) {
            s1.addMoreMedicines();
            s1.display();

            cout << "IF YOU WANT TO MOVE TO MAIN INTERFACE ENTER Y: ";
            cin >> backOption;
            if (backOption == 'Y' || backOption == 'y') {
                continue;
            }
        } else {
            cout << "Invalid option. Try again." << endl;
        }
    }

    return 0;

