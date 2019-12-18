#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/  Flags; void* Name; } ;
typedef  int /*<<< orphan*/  ACPI_STRING ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_INTERFACE_INFO ;

/* Variables and functions */
 void* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_OSI_DYNAMIC ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* AcpiGbl_SupportedInterfaces ; 
 int /*<<< orphan*/  strcpy (void*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtInstallInterface (
    ACPI_STRING             InterfaceName)
{
    ACPI_INTERFACE_INFO     *InterfaceInfo;


    /* Allocate info block and space for the name string */

    InterfaceInfo = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_INTERFACE_INFO));
    if (!InterfaceInfo)
    {
        return (AE_NO_MEMORY);
    }

    InterfaceInfo->Name = ACPI_ALLOCATE_ZEROED (strlen (InterfaceName) + 1);
    if (!InterfaceInfo->Name)
    {
        ACPI_FREE (InterfaceInfo);
        return (AE_NO_MEMORY);
    }

    /* Initialize new info and insert at the head of the global list */

    strcpy (InterfaceInfo->Name, InterfaceName);
    InterfaceInfo->Flags = ACPI_OSI_DYNAMIC;
    InterfaceInfo->Next = AcpiGbl_SupportedInterfaces;

    AcpiGbl_SupportedInterfaces = InterfaceInfo;
    return (AE_OK);
}