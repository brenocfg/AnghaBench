#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Flags; char* Name; struct TYPE_3__* Next; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_INTERFACE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_OSI_INVALID ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_OsiMutex ; 
 TYPE_1__* AcpiGbl_SupportedInterfaces ; 
 int /*<<< orphan*/  AcpiInstallInterface (char*) ; 
 int /*<<< orphan*/  AcpiOsAcquireMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiRemoveInterface (char*) ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 char* strstr (char*,char*) ; 

void
AcpiDbDisplayInterfaces (
    char                    *ActionArg,
    char                    *InterfaceNameArg)
{
    ACPI_INTERFACE_INFO     *NextInterface;
    char                    *SubString;
    ACPI_STATUS             Status;


    /* If no arguments, just display current interface list */

    if (!ActionArg)
    {
        (void) AcpiOsAcquireMutex (AcpiGbl_OsiMutex, ACPI_WAIT_FOREVER);

        NextInterface = AcpiGbl_SupportedInterfaces;
        while (NextInterface)
        {
            if (!(NextInterface->Flags & ACPI_OSI_INVALID))
            {
                AcpiOsPrintf ("%s\n", NextInterface->Name);
            }

            NextInterface = NextInterface->Next;
        }

        AcpiOsReleaseMutex (AcpiGbl_OsiMutex);
        return;
    }

    /* If ActionArg exists, so must InterfaceNameArg */

    if (!InterfaceNameArg)
    {
        AcpiOsPrintf ("Missing Interface Name argument\n");
        return;
    }

    /* Uppercase the action for match below */

    AcpiUtStrupr (ActionArg);

    /* Install - install an interface */

    SubString = strstr ("INSTALL", ActionArg);
    if (SubString)
    {
        Status = AcpiInstallInterface (InterfaceNameArg);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("%s, while installing \"%s\"\n",
                AcpiFormatException (Status), InterfaceNameArg);
        }
        return;
    }

    /* Remove - remove an interface */

    SubString = strstr ("REMOVE", ActionArg);
    if (SubString)
    {
        Status = AcpiRemoveInterface (InterfaceNameArg);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("%s, while removing \"%s\"\n",
                AcpiFormatException (Status), InterfaceNameArg);
        }
        return;
    }

    /* Invalid ActionArg */

    AcpiOsPrintf ("Invalid action argument: %s\n", ActionArg);
    return;
}