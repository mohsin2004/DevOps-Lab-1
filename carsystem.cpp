#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<fstream>

using namespace std;

struct Car
{
	int ID;
	string manufacturer;
	string model;
	int year;
	bool status;
	int rate;
	Car* next;

	Car()
	{
		ID = 0;
		manufacturer = "";
		model = "";
		year = 0;
		status = false;
		rate = 0;
		next = NULL;
	}
};

struct Customer
{
	int ID;
	string name;
	string contact;
	Customer* next;

	Customer()
	{
		ID = 0;
		name = "";
		contact = "";
		next = NULL;
	}
};

struct RentalRecord
{
	int ID;
	int customerID;
	int carID;
	string rentalDate;
	string returnDate;
	int totalCost;
	RentalRecord* next;

	RentalRecord()
	{
		ID = 0;
		customerID = 0;
		carID = 0;
		rentalDate = "";
		returnDate = "";
		totalCost = 0;
		next = NULL;
	}
};

class FileHandler
{
public:
	void loadCarsData(Car*& head)
	{
		ifstream file("cars.txt");

		if (!file.is_open())
		{
			cout << "\nError opening file!\n\n";
			return;
		}
		
		Car* newCar = new Car;

		while (file >> newCar->ID >> newCar->manufacturer >> newCar->model >> newCar->year >> newCar->rate >> newCar->status)
		{
			
			newCar->next = NULL;

			if (head == NULL)
			{
				head = newCar;
			}
			else
			{
				Car* temp = head;

				while (temp->next != NULL)
				{
					temp = temp->next;
				}

				temp->next = newCar;
			}
		}

		file.close();
	}

	void saveCarsData(Car*& head)
	{
		ofstream file("cars.txt", ios::trunc);

		if (!file.is_open())
		{
			cout << "\nError opening file!\n\n";
			return;
		}

		Car* temp = head;

		while (temp != NULL)
		{
			file << temp->ID << " " << temp->manufacturer << " " << temp->model << " " << temp->year << " " << temp->rate << " " << temp->status << endl;

			temp = temp->next;
		}

		file.close();
	}

	void loadCustomersData(Customer*& head)
	{
		ifstream file("customers.txt");

		if (!file.is_open())
		{
			cout << "\nError opening file!\n\n";
			return;
		}

		Customer* newCust = new Customer;

		while (file >> newCust->ID >> newCust->name >> newCust->contact)
		{
			newCust->next = NULL;

			if (head == NULL)
			{
				head = newCust;
			}
			else
			{
				Customer* temp = head;

				while (temp->next != NULL)
				{
					temp = temp->next;
				}

				temp->next = newCust;
			}
		}

		file.close();
	}

	void saveCustomersData(Customer*& head)
	{
		ofstream file("customers.txt", ios::trunc);

		if (!file.is_open())
		{
			cout << "\nError opening file!\n\n";
			return;
		}

		Customer* temp = head;

		while (temp != NULL)
		{
			file << temp->ID << " " << temp->name << " " << temp->contact << endl;
			temp = temp->next;
		}

		file.close();
	}

	void loadRecordsData(RentalRecord*& head)
	{
		ifstream file("records.txt");

		if (!file.is_open())
		{
			cout << "\nError opening file!\n\n";
			return;
		}

		RentalRecord* newRecord = new RentalRecord;

		while (file >> newRecord->ID >> newRecord->carID >> newRecord->customerID >> newRecord->rentalDate >> newRecord->returnDate >> newRecord->totalCost)
		{
			newRecord->next = NULL;

			if (head == NULL)
			{
				head = newRecord;
			}
			else
			{
				RentalRecord* temp = head;

				while (temp->next != NULL)
				{
					temp = temp->next;
				}

				temp->next = newRecord;
			}
		}

		file.close();
	}

	void saveRecordsData(RentalRecord*& head)
	{
		ofstream file("records.txt", ios::trunc);

		if (!file.is_open())
		{
			cout << "\nError opening file!\n\n";
			return;
		}

		RentalRecord* temp = head;

		while (temp != NULL)
		{
			file << temp->ID << " " << temp->carID << " " << temp->customerID << " " << temp->rentalDate << " " << temp->returnDate << " " << temp->totalCost << endl;

			temp = temp->next;
		}

		file.close();
	}
};

class CarRentalSystem
{
private:
	Car* headCar;
	Customer* headCustomer;
	RentalRecord* headRecord;
	FileHandler file;
public:
	CarRentalSystem()
	{
		headCar = NULL;
		headCustomer = NULL;
		headRecord = NULL;

		file.loadCarsData(headCar);
		file.loadCustomersData(headCustomer);
		file.loadRecordsData(headRecord);
	}

	~CarRentalSystem()
	{
		file.saveCarsData(headCar);
		file.saveCustomersData(headCustomer);
		file.saveRecordsData(headRecord);
	}

	void addCar()
	{
		Car* newCar = new Car;

		cout << "\nEnter Car Manufacturer: ";
		cin >> newCar->manufacturer;
		cout << "Enter Car Model: ";
		cin >> newCar->model;
		cout << "Enter manufacturing year: ";
		cin >> newCar->year;
		cout << "Enter Rental rate per day: Rs.";
		cin >> newCar->rate;
		newCar->status = true;

		Car* tempCar = headCar;

		if (headCar == NULL)
		{
			newCar->ID = 1;
			headCar = newCar;
		}
		else
		{
			int count = 2;
			while (tempCar->next != NULL)
			{
				count++;
				tempCar = tempCar->next;
			}

			newCar->ID = count;
			tempCar->next = newCar;
		}
		cout << "\nCar Added Successfully!\n\n";
	} // addCar

	void addCustomer()
	{
		Customer* newCust = new Customer;

		cout << "\nEnter Customer First Name: ";
		cin >> newCust->name;
		cout << "Enter Customer Contact: ";
		cin >> newCust->contact;
		
		Customer* tempCust = headCustomer;
		if (headCustomer == NULL)
		{
			newCust->ID = 1;
			newCust->next = NULL;
			headCustomer = newCust;
		}
		else
		{
			int count = 2;
			while (tempCust->next != NULL)
			{
				if (tempCust->name == newCust->name && tempCust->contact == newCust->contact)
				{
					cout << "\nCustomer already in the list!\n\n";
					delete newCust;
					return;
				}
				count++;
				tempCust = tempCust->next;
			}

			newCust->ID = count;
			tempCust->next = NULL;
			tempCust->next = newCust;

			cout << "\nCustomer added successfully!\n\n";
		}
	} // addCustomer

	void CarStatusUpdate()
	{
		int ID;
		cout << "\nEnter Car ID to mark as available: ";
		cin >> ID;

		Car* temp = headCar;
		while (temp != NULL && temp->ID != ID)
		{
			temp = temp->next;
		}

		if (temp == NULL)
		{
			cout << "\nInvalid Car ID!\n\n";
		}
		else
		{
			cout << "\nCar marked as available successfully!\n\n";
		}
	}
	void allCustomers()
	{
		if (headCustomer == NULL)
		{
			cout << "\nThere are no customers!\n\n";
			return;
		}
		Customer* temp = headCustomer;

		cout << "\n\tCUSTOMERS\n\n";
		cout << setw(5) << left << "ID" << setw(20) << left << "NAME" << setw(15) << left << "CONTACT" << endl;
		while (temp != NULL)
		{
			cout << endl << setw(5) << left << temp->ID << setw(20) << left << temp->name << " " << setw(15) << left << temp->contact;

			temp = temp->next;
		}

		cout << endl << endl;
	}

	void allCars()
	{
		if(headCar == NULL)
		{
			cout << "\nThere are no Cars in list!\n\n";
			return;
		}

		Car* temp = headCar;

		cout << "\n\tALL CARS\n\n";
		cout << setw(5) << left << "ID" << setw(15) << left << "MANUFACTURER" << setw(10) << left << "MODEL" << setw(6) << left <<   "YEAR" << setw(10) << left << "RATE/DAY" << endl;

		while (temp != NULL)
		{
			cout << endl << setw(5) << left << temp->ID << setw(15) << left << temp->manufacturer << setw(10) << left << temp->model << setw(6) << left << temp->year << setw(10) << left << temp->rate;
			temp = temp->next;
		}

		cout << endl << endl;
	}

	void availableCars()
	{
		Car* temp = headCar;

		cout << "\n\tAVAILABLE CARS\n\n";
		cout << setw(5) << left << "ID" << setw(15) << left << "MANUFACTURER" << setw(10) << left << "MODEL" << setw(6) << left << "YEAR" << setw(10) << left << "RATE/DAY" << endl;

		bool flag = false;
		while (temp != NULL)
		{
			if (temp->status == true)
			{
				flag = true;
				cout << endl << setw(5) << left << temp->ID << setw(15) << left << temp->manufacturer << setw(10) << left << temp->model << setw(6) << left << temp->year << setw(10) << left << temp->rate;
			}
			temp = temp->next;
		}


		if (flag == false)
		{
			cout << "\nThere are no cars available!\n\n";
		}
		else
		{
			cout << endl << endl;
		}
	}

	void rentCar()
	{
		int custID, carID, days;

		cout << "\nEnter customer ID: ";
		cin >> custID;

		Customer* tempCust = headCustomer;
		while (tempCust != NULL && tempCust->ID != custID)
		{
			tempCust = tempCust->next;
		}

		if (tempCust == NULL)
		{
			cout << "\nCustomer not found.\n\n";
			return;
		}
		
		cout << endl;
		availableCars();

		cout << "\nRenting a Car for " << tempCust->name;

		cout << "\nEnter Car ID to rent: ";
		cin >> carID;

		Car* tempCar = headCar;
		while (tempCar != NULL && tempCar->ID != carID)
		{
			tempCar = tempCar->next;
		}

		if (tempCar == NULL)
		{
			cout << "\nCar not found.\n\n";
			return;
		}

		if (!tempCar->status)
		{
			cout << "\nCar not available for rent.\n\n";
			return;
		}

		cout << "\nEnter No. of days you want to rent the Car: ";
		cin >> days;

		int totalRent;
		
		totalRent = tempCar->rate * days;
		cout << "\nTotal rent for " << days << " days will be Rs. " << totalRent << endl << endl;

		time_t t = time(0);
		struct tm now;

		localtime_s(&now, &t) != 0;

		struct tm returnDate = now;
		returnDate.tm_mday += days;
		mktime(&returnDate); 

		char rentalDateStr[11];
		strftime(rentalDateStr, sizeof(rentalDateStr), "%d/%m/%Y", &now);

		char returnDateStr[11];
		strftime(returnDateStr, sizeof(returnDateStr), "%d/%m/%Y", &returnDate);

		
		tempCar->status = false;

		RentalRecord* newRecord = new RentalRecord;
		newRecord->customerID = custID;
		newRecord->carID = carID;
		newRecord->rentalDate = rentalDateStr;
		newRecord->returnDate = returnDateStr;
		newRecord->totalCost = totalRent;

		if (headRecord == NULL)
		{
			newRecord->ID = 1;
			headRecord = newRecord;
		}
		else
		{
			int count = 2;
			RentalRecord* tempRecord = headRecord;
			while (tempRecord->next != NULL)
			{
				count++;
				tempRecord = tempRecord->next;
			}
			
			newRecord->ID = count;
			tempRecord->next = newRecord;
		}
	}

	void removeCar()
	{
		int carID;

		cout << "\nEnter car ID to remove: ";
		cin >> carID;

		Car* temp = headCar;
		Car* prev = NULL;
		while (temp != NULL)
		{
			prev = temp;
			if (temp->ID == carID)
			{
				prev->next = temp->next;
				delete temp;
				cout << "\nCar deleted from the list successfully!\n\n";
				return;
			}
			temp = temp->next;
		}

		if (temp == NULL)
		{
			cout << "\nInvalid Car ID!\n\n";
		}
	}

	void AllRecords()
	{
		RentalRecord* tempRecord = headRecord;

		if (tempRecord == NULL)
		{
			cout << "\nThere are no rental records!\n\n";
			return;
		}

		cout << "\n\tALL RENTAL RECORDS\n\n";
		cout << setw(5) << left << "ID" << setw(12) << left << "customerID" << setw(7) << left << "carID" << setw(13) << left << "Rental Date" << setw(13) << left << "Return Date" << setw(10) << left << "Total Rent" << endl;
		while (tempRecord != NULL)
		{
			cout << endl << setw(5) << left << tempRecord->ID << setw(12) << left << tempRecord->customerID << setw(7) << left << tempRecord->carID << setw(13) << left << tempRecord->rentalDate << setw(13) << left << tempRecord->returnDate << setw(10) << left << tempRecord->totalCost;

			tempRecord = tempRecord->next;
		}

		cout << endl << endl;
	}
};

int main()
{
	CarRentalSystem rent;
	int choice;

	while (true)
	{
		system("cls");
		
		cout << "\n\tCar Rental System\n";
		cout << "\n1. Add Customer";
		cout << "\n2. Add Car";
		cout << "\n3. Rent a Car";
		cout << "\n4. Remove Car";
		cout << "\n5. Check Available Cars";
		cout << "\n6. View All Cars";
		cout << "\n7. View All Customers";
		cout << "\n8. View All Records";
		cout << "\n9. Mark Car as Available";
		cout << "\n10. Exit";
		cout << "\nEnter choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1: {
			rent.addCustomer();
			system("pause");
		}
			  break;

		case 2: {
			rent.addCar();
			system("pause");
		}
			  break;

		case 3: {
			rent.rentCar();
			system("pause");
		}
			  break;

		case 4: {
			rent.removeCar();
			system("pause");
		}
			  break;

		case 5: {
			rent.availableCars();
			system("pause");
		}
			  break;

		case 6: {
			rent.allCars();
			system("pause");
		}
			  break;

		case 7: {
			rent.allCustomers();
			system("pause");
		}
			  break; 

		case 8: {
			rent.AllRecords();
			system("pause");
		}
			  break;

		case 9: {
			rent.CarStatusUpdate();
			system("pause");
		}
			  break;

		case 10: {
			cout << "\nGood bye!\n\n";
			return 0;
		}
			  break;

		default: {
			cout << "\nEnter valid choice!\n\n";
			system("pause");
		}
			   break;
		} // switch
	} // while

	return 0;
}