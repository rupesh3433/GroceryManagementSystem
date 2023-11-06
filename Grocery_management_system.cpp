#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Product {
public:
    string name;
    double price;
    int quantity;

    Product(const string& n, double p, int q) : name(n), price(p), quantity(q) {}
};

class GroceryManager {
private:
    vector<Product> products;

public:
    void addProduct(const string& name, double price, int quantity) {
        products.emplace_back(name, price, quantity);
    }

    void listAllProducts() {
        for (const Product& product : products) {
            cout << "Name: " << product.name << "\tPrice: " << product.price << "\tQuantity: " << product.quantity << endl;
        }
    }

    void searchProduct(const string& name) {
        for (const Product& product : products) {
            if (product.name == name) {
                cout << "Name: " << product.name << "\tPrice: " << product.price << "\tQuantity: " << product.quantity << endl;
                return;
            }
        }
        cout << "Product not found." << endl;
    }

    void sellProduct(const string& name, int quantity) {
        for (Product& product : products) {
            if (product.name == name) {
                product.quantity += quantity;
                cout << "Added " << quantity << " " << name << " to the inventory." << endl;
                return;
            }
        }
        cout << "Product not found." << endl;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const Product& product : products) {
            file << product.name << " " << product.price << " " << product.quantity << endl;
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "File not found." << endl;
            return;
        }

        products.clear();

        string name;
        double price;
        int quantity;

        while (file >> name >> price >> quantity) {
            products.emplace_back(name, price, quantity);
        }

        file.close();
    }
};

void displayManagerMenu() {
    cout << "Manager Menu:" << endl;
    cout << "1. List all products" << endl;
    cout << "2. Search for a product" << endl;
    cout << "3. Add a product" << endl;
    cout << "4. Sell a product" << endl;
    cout << "5. Save Products to File" << endl;
    cout << "6. Load Products from File" << endl;
    cout << "7. Exit" << endl;
}

void displayCustomerMenu() {
    cout << "Customer Menu:" << endl;
    cout << "1. List all products" << endl;
    cout << "2. Search for a product" << endl;
    cout << "3. Buy a product" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    GroceryManager manager;
    int choice;
    string checkingManager;
    bool isManagerAccess;
    cout<<"-----------------------------------------------------------------------------------\n";
    cout<<"Are you A manager Or Customer? [ 'M'/'m' for manager && 'C'/'c' for Customer] ::-- ";
    cin >> checkingManager;
    if (checkingManager == "M" || checkingManager == "m")
    {
        isManagerAccess = true;
    }
    else if(checkingManager == "C" || checkingManager == "c"){
        isManagerAccess = false;
    }
    else{
        cout<<"Invalid Choice\nExiting the program";
        return 0;
    }
    

    while (true) {
        if (isManagerAccess) {
            displayManagerMenu();
            cout<<"\nEnter Your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    manager.listAllProducts();
                    break;
                case 2:
                    {
                        string name;
                        cout << "Enter the name of the product: ";
                        cin >> name;
                        manager.searchProduct(name);
                    }
                    break;
                case 3:
                    {
                        string name;
                        double price;
                        int quantity;
                        cout << "Enter the name of the product: ";
                        cin >> name;
                        cout << "Enter the price of the product: ";
                        cin >> price;
                        cout << "Enter the initial quantity: ";
                        cin >> quantity;
                        manager.addProduct(name, price, quantity);
                    }
                    break;
                case 4:
                    {
                        string name;
                        int quantity;
                        cout << "Enter the name of the product to sell: ";
                        cin >> name;
                        cout << "Enter the quantity to sell: ";
                        cin >> quantity;
                        manager.sellProduct(name, quantity);
                    }
                    break;
                case 5:
                    manager.saveToFile("products.txt");
                    cout << "Products saved to file." << endl;
                    break;
                case 6:
                    manager.loadFromFile("products.txt");
                    cout << "Products loaded from file." << endl;
                    break;
                case 7:
                    cout << "Exiting the program." << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } else {
            displayCustomerMenu();
            cout<<"\nEnter Your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    manager.listAllProducts();
                    break;
                case 2:
                    {
                        string name;
                        cout << "Enter the name of the product: ";
                        cin >> name;
                        manager.searchProduct(name);
                    }
                    break;
                case 3:
                    {
                        string name;
                        int quantity;
                        cout << "Enter the name of the product to buy: ";
                        cin >> name;
                        cout << "Enter the quantity to buy: ";
                        cin >> quantity;
                        manager.sellProduct(name, quantity);
                    }
                    break;
                case 4:
                    cout << "Exiting the program." << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    return 0;
}
