#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDbSetOutputDestination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDbWalkAndMatchName ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 int /*<<< orphan*/  AcpiUtStrupr (char*) ; 
 int /*<<< orphan*/  AcpiWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

ACPI_STATUS
AcpiDbFindNameInNamespace (
    char                    *NameArg)
{
    char                    AcpiName[5] = "____";
    char                    *AcpiNamePtr = AcpiName;


    if (strlen (NameArg) > ACPI_NAMESEG_SIZE)
    {
        AcpiOsPrintf ("Name must be no longer than 4 characters\n");
        return (AE_OK);
    }

    /* Pad out name with underscores as necessary to create a 4-char name */

    AcpiUtStrupr (NameArg);
    while (*NameArg)
    {
        *AcpiNamePtr = *NameArg;
        AcpiNamePtr++;
        NameArg++;
    }

    /* Walk the namespace from the root */

    (void) AcpiWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
        ACPI_UINT32_MAX, AcpiDbWalkAndMatchName, NULL, AcpiName, NULL);

    AcpiDbSetOutputDestination (ACPI_DB_CONSOLE_OUTPUT);
    return (AE_OK);
}