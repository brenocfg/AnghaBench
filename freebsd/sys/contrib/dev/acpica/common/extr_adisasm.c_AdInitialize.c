#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int MaxTableCount; int /*<<< orphan*/  Tables; scalar_t__ CurrentTableCount; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 char* AcpiFormatException (int /*<<< orphan*/ ) ; 
 TYPE_1__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiNsRootInitialize () ; 
 int /*<<< orphan*/  AcpiOsInitialize () ; 
 int /*<<< orphan*/  AcpiUtInitGlobals () ; 
 int /*<<< orphan*/  AcpiUtMutexInitialize () ; 
 int /*<<< orphan*/  LocalTables ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

ACPI_STATUS
AdInitialize (
    void)
{
    ACPI_STATUS             Status;


    /* ACPICA subsystem initialization */

    Status = AcpiOsInitialize ();
    if (ACPI_FAILURE (Status))
    {
        fprintf (stderr, "Could not initialize ACPICA subsystem: %s\n",
            AcpiFormatException (Status));

        return (Status);
    }

    Status = AcpiUtInitGlobals ();
    if (ACPI_FAILURE (Status))
    {
        fprintf (stderr, "Could not initialize ACPICA globals: %s\n",
            AcpiFormatException (Status));

        return (Status);
    }

    Status = AcpiUtMutexInitialize ();
    if (ACPI_FAILURE (Status))
    {
        fprintf (stderr, "Could not initialize ACPICA mutex objects: %s\n",
            AcpiFormatException (Status));

        return (Status);
    }

    Status = AcpiNsRootInitialize ();
    if (ACPI_FAILURE (Status))
    {
        fprintf (stderr, "Could not initialize ACPICA namespace: %s\n",
            AcpiFormatException (Status));

        return (Status);
    }

    /* Setup the Table Manager (cheat - there is no RSDT) */

    AcpiGbl_RootTableList.MaxTableCount = 1;
    AcpiGbl_RootTableList.CurrentTableCount = 0;
    AcpiGbl_RootTableList.Tables = LocalTables;

    return (AE_OK);
}