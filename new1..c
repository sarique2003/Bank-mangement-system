#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, j;
int main_exit;

struct date
{
    int day, month, yr;
};

struct Details
{
    char name[100];
    int acno, age;
    char address[100], acc_type[20], citizen[20];
    double phone;
    float amt;
    struct date dob;
    struct date depos;
    struct date with;

} add, upd, check, rem, trans;

void menu();
float interest(float t, float amount, int rate);
void view_list();
void transact();
void close(void);
void new_acc();
void edit();
void erase();
void see();

int main()
{
    menu();
    return 0;
}

void menu()
{
    int choice;
    printf("\n\t*-*-*-*-*-*-*[BANKING MANAGEMENT SYSTEM]*-*-*-*-*-*-*\n\n\t\t----------------- MENU-------------------        ");
    printf("\n\n\t1. Create new account\n\t2. Update existing account\n\t3. Transactions\n\t4. Check the details of existing account\n\t5. Remove existing account\n\t6. View customer's list\n\t7. Loan \n\t8. Exit\n\n\tEnter your choice : ");
    scanf(" %d", &choice);

    switch (choice)
    {
    case 1:
        new_acc();
        break;
    case 2:
        edit();
        break;
    case 3:
        transact();
        break;
    case 4:
        see();
        break;
    case 5:
        erase();
        break;
    case 6:
        view_list();
        break;
    case 7:
         printf("--------------------------------------------------------\n");
         printf("Contact Loan dept.of bank\n \t Email= Loans@iiitkalyani.ac.in   \n");
         printf("---------------------------------------------------------\n");
    case 8:
        close();
        break;
    }
}

float interest(float t, float amount, int rate)
{
    float SI;
    SI = (rate * t * amount) / 100;
    return (SI);
}

void view_list()
{
    FILE *view;
    view = fopen("IIITkalyanibank.csv", "r");
    int test = 0;
    printf("\nACC. NO.\t\tNAME\t\t\tADDRESS\t\t\tPHONE\n");

    while (feof(view) == 0)
    {
        fscanf(view, "%d, %[^,], %d,/,%d,/,%d, %d, %[^,], %[^,], %lf, %[^,], %f, %d,/,%d,/,%d\n", &add.acno, add.name, &add.dob.day, &add.dob.month, &add.dob.yr, &add.age, add.address, add.citizen, &add.phone, add.acc_type, &add.amt, &add.depos.day, &add.depos.month, &add.depos.yr);

        printf("\n%6d\t\t %10s\t\t\t%10s\t\t%.0lf", add.acno, add.name, add.address, add.phone);
        test++;
    }

    fclose(view);
    if (test == 0)
    {
        printf("\n---------!!NO RECORDS FOUND!-----------------!\n");
    }

    printf("\n\n{Enter 1 to go to the main menu and 0 to exit:}");
    scanf(" %d", &main_exit);

    if (main_exit == 1)
        menu();
}

void transact()
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("IIITkalyanibank.csv", "r");
    newrec = fopen("new.csv", "w");

    printf("\nEnter the account no. of the customer : ");
    scanf(" %d", &trans.acno);
    while (feof(old) == 0)
    {
        fscanf(old, "%d, %[^,], %d,/,%d,/,%d, %d, %[^,], %[^,], %lf, %[^,], %f, %d,/,%d,/,%d\n", &add.acno, add.name, &add.dob.day, &add.dob.month, &add.dob.yr, &add.age, add.address, add.citizen, &add.phone, add.acc_type, &add.amt, &add.depos.day, &add.depos.month, &add.depos.yr);

        if (add.acno == trans.acno)
        {
            test = 1;
            if (strcasecmp(add.acc_type, "fixed1") == 0 || strcasecmp(add.acc_type, "fixed2") == 0 || strcasecmp(add.acc_type, "fixed3") == 0)
            {
                printf("\n\n!!----------You cannot deposit or withdraw cash in a fixed account------------!!\n");
                menu();
            }
            printf("\n\nDo you want to\n\t1. Deposit\n\t2. Withdraw\n\nEnter your choice(1 for deposit and 2 for withdraw) : ");
            scanf(" %d", &choice);
            if (choice == 1)
            {
                printf("\nEnter the amount you want to deposit : Rs. ");
                scanf(" %f", &trans.amt);
                add.amt += trans.amt;
                fprintf(newrec, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
                printf("\n\nDeposited successfully!");
            }
            else
            {
                printf("Enter the amount you want to withdraw:Rs. ");
                scanf(" %f", &trans.amt);
                add.amt -= trans.amt;
                fprintf(newrec, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
                printf("\n\nWithdrawn successfully!");
            }
        }
        else
        {
            fprintf(newrec, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
        }
    }
    fclose(old);
    fclose(newrec);
    remove("IIITkalyanibank.csv");
    rename("new.csv", "IIITkalyanibank.csv");

    if (test != 1)
    {
        printf("\n\nRecord not found!!");
        printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit : ");
        scanf(" %d", &main_exit);
        if (main_exit == 0)
            transact();
        else if (main_exit == 1)
            menu();
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit : ");
        scanf(" %d", &main_exit);
        if (main_exit == 1)
            menu();
    }
}

void close(void)
{
    printf("\n\n\n\nThis C Project is developed by MOHD SARIQUE(713) & RAHUL DEWANGAN(725)\n\n");
}

void new_acc()
{
    int ch;
    FILE *ptr;
    ptr = fopen("IIITkalyanibank.csv", "a+");
    if (ptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    else
        printf("\nFile opened successfully\n");

account_no:
    printf("*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n");
    printf("\n\t\t\t-----------////ENTER CREDENTIALS/////--------------------");
    printf("\n\nEnter today's date (dd/mm/yyyy) : ");
    scanf(" %d/%d/%d", &add.depos.day, &add.depos.month, &add.depos.yr);
    printf("\nEnter the account number : ");
    scanf(" %d", &check.acno);
    while (feof(ptr) == 0)
    {
        fscanf(ptr, "%d, %[^,], %d,/,%d,/,%d, %d, %[^,], %[^,], %lf, %[^,], %f, %d,/,%d,/,%d\n", &add.acno, add.name, &add.dob.day, &add.dob.month, &add.dob.yr, &add.age, add.address, add.citizen, &add.phone, add.acc_type, &add.amt, &add.depos.day, &add.depos.month, &add.depos.yr);
        if (check.acno == add.acno)
        {
            printf("\nAccount no. already exsists!\n");
            goto account_no;
        }
    }
    add.acno = check.acno;
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
    printf("\nEnter the name : ");
    scanf(" %[^\n]%*c", add.name);
    printf("\nEnter the date of birth (dd/mm/yyyy) : ");
    scanf(" %d/%d/%d", &add.dob.day, &add.dob.month, &add.dob.yr);
    printf("\nEnter the age : ");
    scanf(" %d", &add.age);
    printf("\nEnter the address : ");
    scanf(" %[^\n]%*c", add.address);
    printf("\nEnter the citizenship number : ");
    scanf(" %s", add.citizen);
    printf("\nEnter the phone number : ");
    scanf(" %lf", &add.phone);
    printf("\nEnter the amount to deposit : Rs.");
    scanf(" %f", &add.amt);
    printf("\nType of account:\n\t# Saving\n\t# Current\n\t# Salary\n\t# Fixed1(for 1 year)\n\t# Fixed2(for 2 years)\n\t# Fixed3(for 3 years)\nEnter your choice : ");
    scanf(" %s", add.acc_type);
    printf("~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");

    fprintf(ptr, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);

    fclose(ptr);
    printf("\n\t ~*~*~*~*~*~*~*~*~*~*~* Account created successfully!! ~*~*~*~*~*~*~*~*~*~*~");

add_invalid:
    printf("\n\n\t\tEnter 1 to go to the main menu and 0 to exit : ");
    scanf(" %d", &main_exit);
    if (main_exit == 1)
        menu();
    else if (main_exit == 0)
        close();
    else
    {
        printf("\nInvalid!\a");
        goto add_invalid;
    }
}

void edit()
{
    int choice, test = 0;
    FILE *old, *newrec;
    old = fopen("IIITkalyanibank.csv", "r");
    newrec = fopen("new.csv", "w");

    printf("\nEnter the account no. of the customer whose info you want to change : ");
    scanf(" %d", &upd.acno);

    while (feof(old) == 0)
    {
        fscanf(old, "%d, %[^,], %d,/,%d,/,%d, %d, %[^,], %[^,], %lf, %[^,], %f, %d,/,%d,/,%d\n", &add.acno, add.name, &add.dob.day, &add.dob.month, &add.dob.yr, &add.age, add.address, add.citizen, &add.phone, add.acc_type, &add.amt, &add.depos.day, &add.depos.month, &add.depos.yr);

        if (add.acno == upd.acno)
        {
            test = 1;
            printf("\nWhich information do you want to change ?\n1. Address\n2. Phone\n\nEnter your choice(1 for address and 2 for phone):");
            scanf(" %d", &choice);
            if (choice == 1)
            {
                printf("\nEnter the new address : ");
                scanf(" %[^\n]%*c", upd.address);
                fprintf(newrec, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, upd.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
                printf("\nChanges saved!\n");
            }
            else if (choice == 2)
            {
                printf("\nEnter the new phone number : ");
                scanf(" %lf", &upd.phone);
                fprintf(newrec, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, upd.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
                printf("\nChanges saved!\n");
            }
        }
        else
            fprintf(newrec, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
    }
    fclose(old);
    fclose(newrec);
    remove("IIITkalyanibank.csv");
    rename("new.csv", "IIITkalyanibank.csv");

    if (test != 1)
    {
        printf("\nRecord not found!!\n");
    edit_invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf(" %d", &main_exit);
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            edit();
        else
        {
            printf("\nInvalid!\n");
            goto edit_invalid;
        }
    }
    else
    {
        printf("\n\n\nEnter 1 to go to the main menu and 0 to exit : ");
        scanf(" %d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

void erase()
{
    FILE *old, *newrec;
    int test = 0;
    old = fopen("IIITkalyanibank.csv", "r");
    newrec = fopen("new.csv", "w");
    printf("Enter the account no. of the customer you want to delete:");
    scanf(" %d", &rem.acno);
    while (feof(old) == 0)
    {
        fscanf(old, "%d, %[^,], %d,/,%d,/,%d, %d, %[^,], %[^,], %lf, %[^,], %f, %d,/,%d,/,%d\n", &add.acno, add.name, &add.dob.day, &add.dob.month, &add.dob.yr, &add.age, add.address, add.citizen, &add.phone, add.acc_type, &add.amt, &add.depos.day, &add.depos.month, &add.depos.yr);

        if (add.acno != rem.acno)
            fprintf(newrec, "%d, %s, %d,/,%d,/,%d, %d, %s, %s, %lf, %s, %f, %d,/,%d,/,%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);

        else
        {
            test++;
            printf("\nRecord deleted successfully!\n");
        }
    }
    fclose(old);
    fclose(newrec);
    remove("IIITkalyanibank.csv");
    rename("new.csv", "IIITkalyanibank.csv");
    if (test == 0)
    {
        printf("\nRecord not found!!\n");
    erase_invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit : ");
        scanf(" %d", &main_exit);

        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            erase();
        else
        {
            printf("\nInvalid!\n");
            goto erase_invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit : ");
        scanf(" %d", &main_exit);
        if (main_exit == 1)
            menu();
        else
            close();
    }
}

void see()
{
    FILE *ptr;
    int test = 0, rate;
    int choice;
    float time;
    float intrst;
    ptr = fopen("IIITkalyanibank.csv", "r");
    printf("\nDo you want to check by\n1. Account no.\n2. Name\nEnter your choice : ");
    scanf(" %d", &choice);
    if (choice == 1)
    {
        printf("\nEnter the account number : ");
        scanf(" %d", &check.acno);

        while (feof(ptr) == 0)
        {
            fscanf(ptr, "%d, %[^,], %d,/,%d,/,%d, %d, %[^,], %[^,], %lf, %[^,], %f, %d,/,%d,/,%d\n", &add.acno, add.name, &add.dob.day, &add.dob.month, &add.dob.yr, &add.age, add.address, add.citizen, &add.phone, add.acc_type, &add.amt, &add.depos.day, &add.depos.month, &add.depos.yr);

            if (add.acno == check.acno)
            {
                test = 1;
                printf("\n**--**--**--**--**--**--**--**--**--**--**--**--**--**--**--**--**--**--**--**\n");
                printf("\n* Account NO. \t : %d\n* Name \t\t : %s \n* DOB \t\t : %d/%d/%d \n* Age \t\t : %d \n* Address \t : %s \n*Citizenship No   : %s \n* Phone number     : %.0lf \n* Type Of Account  : %s \n* Amount deposited : Rs. %.2f \n* Date Of Deposit  : %d/%d/%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
                if (strcasecmp(add.acc_type, "fixed1") == 0)
                {
                    time = 1.0;
                    rate = 3.0;
                    intrst = interest(time, add.amt, rate);
                    printf("\n-----------[You will get Rs. %.2f as interest on %d/%d/%d]-----------\n\n", intrst, add.depos.day, add.depos.month, add.depos.yr + 1);
                }
                else if (strcasecmp(add.acc_type, "fixed2") == 0)
                {
                    time = 2.0;
                    rate = 3.7;
                    intrst = interest(time, add.amt, rate);
                    printf("\n----------[You will get Rs. %.2f as interest on %d/%d/%d]------------\n\n", intrst, add.depos.day, add.depos.month, add.depos.yr + 2);
                }
                else if (strcasecmp(add.acc_type, "fixed3") == 0)
                {
                    time = 3.0;
                    rate = 4.5;
                    intrst = interest(time, add.amt, rate);
                    printf("\n-----------[You will get Rs. %.2f as interest on %d/%d/%d]----------\n\n", intrst, add.depos.day, add.depos.month, add.depos.yr + 3);
                }
                else if (strcasecmp(add.acc_type, "saving") == 0)
                {
                    time = (1.0 / 12.0);
                    rate = 4;
                    intrst = interest(time, add.amt, rate);
                    printf("\n-----------[You will get Rs. %.2f as interest on %d of every month]------------\n\n", intrst,add.depos.day);
                }
                else if (strcasecmp(add.acc_type, "current") == 0)
                {
                    printf("\n---------[You will get no interest]--------\n\n");
                }
                else if (strcasecmp(add.acc_type, "salary") == 0)
                {
                    printf("\n----------[You will get no interest]---------\n\n");
                }
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]%*c", check.name);
        while (feof(ptr) == 0)
        {
            fscanf(ptr, "%d, %[^,], %d,/,%d,/,%d, %d, %[^,], %[^,], %lf, %[^,], %f, %d,/,%d,/,%d\n", &add.acno, add.name, &add.dob.day, &add.dob.month, &add.dob.yr, &add.age, add.address, add.citizen, &add.phone, add.acc_type, &add.amt, &add.depos.day, &add.depos.month, &add.depos.yr);

            if (strcasecmp(add.name, check.name) == 0)
            {
                test = 1;
                printf("*******************************************************************************\n");
                printf("\n* Account No.: %d\n* Name : %s \n* DOB : %d/%d/%d \n* Age : %d \n* Address : %s \n* Citizenship No : %s \n* Phone number : %.0lf \n* Type Of Account : %s \n* Amount deposited : Rs.%.2f \n* Date Of Deposit : %d/%d/%d\n", add.acno, add.name, add.dob.day, add.dob.month, add.dob.yr, add.age, add.address, add.citizen, add.phone, add.acc_type, add.amt, add.depos.day, add.depos.month, add.depos.yr);
                if (strcasecmp(add.acc_type, "fixed1") == 0)
                {
                    time = 1.0;
                    rate = 3;
                    intrst = interest(time, add.amt, rate);
                    printf("\nYou will get Rs. %.2f as interest on %d/%d/%d\n\n", intrst, add.depos.day, add.depos.month, add.depos.yr + 1);
                }
                else if (strcasecmp(add.acc_type, "fixed2") == 0)
                {
                    time = 2.0;
                    rate = 3.7;
                    intrst = interest(time, add.amt, rate);
                    printf("\nYou will get Rs. %.2f as interest on %d/%d/%d\n\n", intrst, add.depos.day, add.depos.month, add.depos.yr + 2);
                }
                else if (strcasecmp(add.acc_type, "fixed3") == 0)
                {
                    time = 3.0;
                    rate = 4.5;
                    intrst = interest(time, add.amt, rate);
                    printf("\nYou will get Rs. %.2f as interest on %d/%d/%d\n\n", intrst, add.depos.day, add.depos.month, add.depos.yr + 3);
                }
                else if (strcasecmp(add.acc_type, "saving") == 0)
                {
                    time = (1.0 / 12.0);
                    rate = 4;
                    intrst = interest(time, add.amt, rate);
                    printf("\nYou will get Rs. %.2f as interest on %d of every month\n\n", intrst, add.depos.day);
                }
                else if (strcasecmp(add.acc_type, "current") == 0)
                {

                    printf("\nYou will get no interest.\n\n");
                }
                else if (strcasecmp(add.acc_type, "salary") == 0)
                {

                    printf("\nYou will get no interest.\n\n");
                }
            }
        }
    }

    fclose(ptr);
    if (test != 1)
    {
        printf("\nRecord not found!!\n");
    see_invalid:
        printf("\n{-----------------Enter 0 to try again, 1 to return to main menu and 2 to exit--------------} : ");
        scanf(" %d", &main_exit);
        if (main_exit == 1)
            menu();
        else if (main_exit == 2)
            close();
        else if (main_exit == 0)
            see();
        else
        {
            printf("\nInvalid!\n");
            goto see_invalid;
        }
    }
    else
    {
        printf("\n{----------------Enter 1 to go to the main menu and 0 to exit-------------}:");
        scanf("%d", &main_exit);
        if (main_exit == 1)
        {
            menu();
        }
        else
        {
            close();
        }
    }
}
