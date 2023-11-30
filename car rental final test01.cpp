#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include<conio.h>


class Car
{
public:
    std::string name;
    double dailyRate;

    Car(const std::string &name, double dailyRate) : name(name), dailyRate(dailyRate) {}
};

class Rent
{
public:
    std::string customerName;
    Car car;
    int days;

    Rent(const std::string &name, const Car &car, int days) : customerName(name), car(car), days(days) {}

    double calculateTotal()
    {
        double total = car.dailyRate * days;
        if (total >= 1500.0)
        {
            discount = 0.05 * total;
            total -= discount;
        }
        return total;
    }

    void displayInvoice()
    {
        std::cout << "\n\t\t\tCar Rental System - Customer Invoice\n";
        std::cout << "\t\t\tCustomer name: " << customerName << "\n";
        std::cout << "\t\t\tCar: " << car.name << "\n";
        std::cout << "\t\t\tNumber of days: " << days << "\n";
        std::cout<<  "\t\t\tTotal:"<<(car.dailyRate*days)<<"$\n";
        std::cout << "\t\t\tTotal Rent After Discount:" << calculateTotal() << " $\n";
        std::cout << "\t\t\tTotal Discount: " << discount << " $\n";
        std::cout<<std::endl;
        std::cout<<std::endl;

        std::ofstream fileI("Invoice.txt",std::ios::app);
        if(!fileI.is_open())
        {
            std::cout<<"File can't be found"<<std::endl;
        }
        else
        {
            fileI<<"Name:"<<customerName<<"\t"<<"Car:"<<car.name<<"\t"<<"Days:"<<days<<"\t"<<"Total($):"<<calculateTotal()<<"\t"<<"Discount($):"<<discount<<std::endl;
        }


    }

private:
    double discount = 0.0;
};

void changePassword(std::string &password)
{
    std::ifstream filey("cars pass.txt");
    if (!filey.is_open())
    {
        std::cout << "Error finding file" << std::endl;
        return;
    }

    std::string storedpass;
    std::getline(filey >> std::ws, storedpass); /// std::ws is whitespace
    filey.close();

    std::cout << "Enter old password: ";
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == 13) // Enter
            break;
        else if (ch == 8)   // Backspace
        {
            if (password.length() > 0)
            {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            std::cout << '*';
            password.push_back(ch);
        }
    }

    if (storedpass == password)
    {
        std::string newpass, confirmpass;

        std::cout << "\nEnter new password: ";
        std::cin >> newpass;
        std::cout << "Confirm new password: ";
        std::cin >> confirmpass;

        if (newpass == confirmpass)
        {
            std::ofstream filez("cars pass.txt");
            if (!filez.is_open())
            {
                std::cout << "Error finding file" << std::endl;
                return;
            }

            std::string tempPassword = newpass;
            std::cout << "Password successfully changed" << std::endl;
            filez << tempPassword;

            filez.close();
        }
        else
        {
            std::ofstream filez("cars pass.txt");
            if (!filez.is_open())
            {
                std::cout << "Error finding file" << std::endl;
                return;
            }

            std::cout << "Password didn't match. Password not changed." << std::endl;
            filez << storedpass;

            filez.close();
        }
    }
    else
    {
        std::cout << "Password didn't match" << std::endl;
    }
}

void displayWelcomeMessage(const std::string &messageFile)
{
    std::ifstream file(messageFile);
    if (!file)
    {
        throw std::runtime_error("Can't open message file: " + messageFile);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout <<"\t\t\t" <<line << std::endl;
    }
    std::cout<<"\n\n";
}
bool Password(std::string &pass)
{
    std::ifstream filex("cars pass.txt");
    if (!filex.is_open())
    {
        std::cout << "Error finding file\n";
        return false;
    }
    else
    {
        std::string output1;
        std::getline(filex >> std::ws, output1);
        std::string inputPassword;
        char ch;
        std::cout << "\t\t\tEnter password: ";
        while (true)
        {
            ch = _getch();
            if (ch == 13) /// Enter button ASCII value
                break;
            else if (ch == 8)   /// Backspace button ASCII value
            {
                if (inputPassword.length() > 0)
                {
                    std::cout << "\b \b";
                    inputPassword.pop_back();
                }
            }
            else
            {
                std::cout << '*';
                inputPassword.push_back(ch);
            }
        }
        std::cout << std::endl;

        if (inputPassword == output1)
        {
            std::cout << "\t\t\tAccess Granted" << std::endl;
            filex.close();
            pass = inputPassword;
            return true;
        }
        else
        {
            std::cout << "\t\t\tPassword didn't match" << std::endl;
            filex.close();
            return false;
        }
    }
}
void Invoicehistory(const std::string &Memo)
{
    std::ifstream fileIN(Memo);
    if(!fileIN.is_open())
    {
        throw std::runtime_error("File can't be found"+Memo);
    }
    else
    {
        while(fileIN.good())
        {
            std::string Output;
            getline(fileIN,Output);
            std::cout<<"\t\t\t"<<Output<<std::endl;
        }
    }
    fileIN.close();

}
void Update_car_status(const std::string &carlist)
{
    std::string opt;
    std::cout<<"\t\t\tUpdate car list(Y/N)"<<std::endl;
    std::cin>>opt;
    if(opt=="Y")
    {
        std::ifstream fileA(carlist);
        if(!fileA.is_open())
        {
            throw std::runtime_error("File can't be found"+carlist);
        }
        else
        {
            std::string carname;
            double rate;
            while(fileA>>carname>>rate)
            {
                std::cout<<"\t\t\tCar Name: "<<carname<<" "<<"Rate: "<<rate<<"$"<<std::endl;
            }
            fileA.close();
            std::ofstream fileB(carlist,std::ios::app);
            if(!fileB)
            {
                std::cout<<"Error finding file"<<std::endl;
            }
            else
            {
                std::string newcar;
                std::cout<<"Enter new car:\t";
                std::cin>>newcar;
                double newrate;
                std::cout<<"Enter rate of the car:\t";
                std::cin>>newrate;
                fileB<<newcar<<" "<<newrate<<std::endl;
                fileB.close();
            }

        }
    }
    else
    {
        std::cout<<"\t\t\tOK\n"<<std::endl;
    }
}

int main()
{
    std::string inputPassword;
    try
    {
        displayWelcomeMessage("welcome_message.txt");

        std::string option;
        do
        {
            std::cout << "\t\t\tEnter your choice: \n";
            std::cout << "\t\t\t1. Rent a car\n";
            std::cout << "\t\t\t2. Change password\n";
            std::cout<<  "\t\t\t3. Update car status\n";
            std::cout<<  "\t\t\t4. Rent History\n";
            std::cout << "\t\t\t5. Exit\n";
            std::cin >> option;

            if (option == "1")
            {
                bool passwordEntered ="false";
                do
                {
                    passwordEntered = Password(inputPassword);
                }
                while (!passwordEntered);
                std::string name;
                int days;

                std::cout << "\t\t\tEnter Customer's name: ";
                std::cin.ignore(); ///using cin. ignore() to get rid off input related problem because of using cin and getline at the same time
                std::getline(std::cin, name);

                std::ifstream file("cars.txt");
                if (!file)
                {
                    throw std::runtime_error("Can't open config file: cars.txt");
                }

                std::string carName;
                double dailyRate;
                while (file >> carName >> dailyRate)
                {
                    std::cout << "\t\t\tEnter '" << carName << "' for " << carName << " - Rent: " << dailyRate << " $ per day\n";
                }

                std::string chosenCar;
                do
                {
                    std::cin >> chosenCar;
                    file.clear(); ///
                    file.seekg(0, std::ios::beg); ///
                    while (file >> carName >> dailyRate)
                    {
                        if (carName == chosenCar)
                        {
                            std::cout << "\t\t\tNumber of days you want the car: ";
                            do
                            {
                                std::cin >> days;
                                if (days < 0)
                                {
                                    std::cout << "Negative number can't be taken! Enter valid number:" << std::endl;
                                }
                            }
                            while (days < 0);

                            //std::cout << "\t\t\tRent for " << chosenCar << " for " << days << " days will be : " << dailyRate * days << " $ \n";

                            Rent rent(name, Car(chosenCar, dailyRate), days); ///creating object of rent class and passing values
                            rent.displayInvoice();

                            break;
                        }
                    }
                    if (carName != chosenCar)
                    {
                        std::cout << "\t\t\tInvalid choice. Please try again.\n";
                    }
                }
                while (carName != chosenCar);
            }
            else if (option == "2")
            {
                changePassword(inputPassword);
            }
            else if(option=="3")
            {
                bool passwordEntered="false";
                do
                {
                    passwordEntered=Password(inputPassword);
                }
                while(!passwordEntered);
                Update_car_status("cars.txt");

            }
            else if(option=="4")
            {
                bool passwordEntered="false";
                do
                {
                    passwordEntered=Password(inputPassword);
                }
                while(!passwordEntered);

                Invoicehistory("Invoice.txt");

            }
            else if (option == "5")
            {
                break;
            }

            else
            {
                std::cout << "\t\t\tInvalid choice. Please try again.\n";
            }
        }
        while (true);
    }
    catch (const std::exception &ex)
    {
        std::cout << "An error occurred: " << ex.what() << "\n";
    }

    return 0;
}


