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
 int /*<<< orphan*/  ACPI_DB_READ_METHOD ; 
 int /*<<< orphan*/  ACPI_DB_WRITE_METHOD ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AcpiDbTestOneObject ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiInstallMethod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadHandle ; 
 int /*<<< orphan*/  ReadMethodCode ; 
 int /*<<< orphan*/  WriteHandle ; 
 int /*<<< orphan*/  WriteMethodCode ; 

__attribute__((used)) static void
AcpiDbTestAllObjects (
    void)
{
    ACPI_STATUS             Status;


    /* Install the debugger read-object control method if necessary */

    if (!ReadHandle)
    {
        Status = AcpiInstallMethod (ReadMethodCode);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("%s, Could not install debugger read method\n",
                AcpiFormatException (Status));
            return;
        }

        Status = AcpiGetHandle (NULL, ACPI_DB_READ_METHOD, &ReadHandle);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("Could not obtain handle for debug method %s\n",
                ACPI_DB_READ_METHOD);
            return;
        }
    }

    /* Install the debugger write-object control method if necessary */

    if (!WriteHandle)
    {
        Status = AcpiInstallMethod (WriteMethodCode);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("%s, Could not install debugger write method\n",
                AcpiFormatException (Status));
            return;
        }

        Status = AcpiGetHandle (NULL, ACPI_DB_WRITE_METHOD, &WriteHandle);
        if (ACPI_FAILURE (Status))
        {
            AcpiOsPrintf ("Could not obtain handle for debug method %s\n",
                ACPI_DB_WRITE_METHOD);
            return;
        }
    }

    /* Walk the entire namespace, testing each supported named data object */

    (void) AcpiWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
        ACPI_UINT32_MAX, AcpiDbTestOneObject, NULL, NULL, NULL);
}