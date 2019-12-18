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
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AcpiGbl_DbCommandComplete ; 
 int /*<<< orphan*/  AcpiGbl_DbCommandReady ; 
 int /*<<< orphan*/  AcpiGbl_DbCommandSignalsInitialized ; 
 int /*<<< orphan*/  AcpiOsAcquireMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsCreateMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiOsDeleteMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

ACPI_STATUS
AcpiOsInitializeDebugger (
    void)
{
    ACPI_STATUS             Status;


    /* Create command signals */

    Status = AcpiOsCreateMutex (&AcpiGbl_DbCommandReady);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }
    Status = AcpiOsCreateMutex (&AcpiGbl_DbCommandComplete);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorReady;
    }

    /* Initialize the states of the command signals */

    Status = AcpiOsAcquireMutex (AcpiGbl_DbCommandComplete,
        ACPI_WAIT_FOREVER);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorComplete;
    }
    Status = AcpiOsAcquireMutex (AcpiGbl_DbCommandReady,
        ACPI_WAIT_FOREVER);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorComplete;
    }

    AcpiGbl_DbCommandSignalsInitialized = TRUE;
    return (Status);

ErrorComplete:
    AcpiOsDeleteMutex (AcpiGbl_DbCommandComplete);
ErrorReady:
    AcpiOsDeleteMutex (AcpiGbl_DbCommandReady);
    return (Status);
}