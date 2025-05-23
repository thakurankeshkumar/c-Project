#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ✅ Unit 6: Macro
#define MAX_CUSTOMERS 100
#define MAX_NAME 50
#define MAX_BALANCE 1000000

// ✅ Unit 6: Structure
struct Account
{
    int acc_no;
    char name[MAX_NAME];
    float balance;
};

// ✅ Unit 6: Union (Not strictly needed here, but for syllabus coverage)
union AccountType
{
    char savings[10];
    char current[10];
};

// ✅ Function Prototypes – Unit 3
void deposit(struct Account *acc, float amount);
void withdraw(struct Account *acc, float amount);
void viewAccount(struct Account acc);
int search(struct Account *arr, int n, int acc_no);
void sort(struct Account *arr, int n);
void menu(struct Account *arr, int n);

// ✅ Main Function – Includes Unit 5 (pointers, malloc)
int main()
{
    int n;
    printf("Enter number of customers: ");
    scanf("%d", &n);

    struct Account *customers = (struct Account *)malloc(n * sizeof(struct Account));
    printf("Welcome to SOFTECH DEVELOPEMENT....\n");
    printf("Today i am going to start my journy\n");

    // Input customer details
    for (int i = 0; i < n; i++)
    {
        printf("Enter details for customer %d\n", i + 1);
        printf("Account Number: ");
        scanf("%d", &customers[i].acc_no);
        getchar(); // flush newline
        printf("Name: ");
        fgets(customers[i].name, MAX_NAME, stdin);
        customers[i].name[strcspn(customers[i].name, "\n")] = 0; // remove newline
        printf("Initial Balance: ");
        scanf("%f", &customers[i].balance);
    }

    menu(customers, n); // Start operations

    free(customers); // ✅ Unit 5: Free allocated memory
    return 0;
}

// ✅ Unit 3: User-defined functions
void deposit(struct Account *acc, float amount)
{
    if (acc->balance + amount > MAX_BALANCE)
    {
        printf("Cannot exceed max balance limit.\n");
        return;
    }
    acc->balance += amount;
    printf("Deposit successful. New balance: %.2f\n", acc->balance);
}

void withdraw(struct Account *acc, float amount)
{
    if (acc->balance < amount)
    {
        printf("Insufficient balance!\n");
    }
    else
    {
        acc->balance -= amount;
        printf("Withdrawal successful. New balance: %.2f\n", acc->balance);
    }
}

void viewAccount(struct Account acc)
{
    printf("Account No: %d\n", acc.acc_no);
    printf("Name      : %s\n", acc.name);
    printf("Balance   : %.2f\n", acc.balance);
}

// ✅ Binary Search – Unit 4
int search(struct Account *arr, int n, int acc_no)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid].acc_no == acc_no)
            return mid;
        else if (arr[mid].acc_no < acc_no)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// ✅ Bubble Sort – Unit 4
void sort(struct Account *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].balance > arr[j + 1].balance)
            {
                struct Account temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Accounts sorted by balance.\n");
}

// ✅ Menu with recursion – Unit 2, Unit 3
void menu(struct Account *arr, int n)
{
    int choice, acc_no, index;
    float amount;
    char again;

    do
    {
        printf("\n--- Banking Menu ---\n");
        printf("1. Deposit\n2. Withdraw\n3. View Account\n4. Sort by Balance\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3)
        {
            printf("Enter Account Number: ");
            scanf("%d", &acc_no);
            index = search(arr, n, acc_no);
            if (index == -1)
            {
                printf("Account not found!\n");
                continue;
            }
        }

        switch (choice)
        {
        case 1:
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            deposit(&arr[index], amount);
            break;
        case 2:
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            withdraw(&arr[index], amount);
            break;
        case 3:
            viewAccount(arr[index]);
            break;
        case 4:
            sort(arr, n);
            for (int i = 0; i < n; i++)
            {
                viewAccount(arr[i]);
            }
            break;
        case 5:
            printf("Thank you for using our banking system.\n");
            return;
        default:
            printf("Invalid choice!\n");
        }

        printf("Do you want to perform another operation? (Y/N): ");
        getchar();
        scanf("%c", &again);

    } while (again == 'Y' || again == 'y');
}

