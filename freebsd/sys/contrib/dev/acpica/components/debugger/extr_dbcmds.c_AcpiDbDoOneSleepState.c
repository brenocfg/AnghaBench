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
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t ACPI_S_STATES_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiEnterSleepState (size_t) ; 
 int /*<<< orphan*/  AcpiEnterSleepStatePrep (size_t) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * AcpiGbl_SleepStateNames ; 
 int /*<<< orphan*/  AcpiGetSleepTypeData (size_t,size_t*,size_t*) ; 
 int /*<<< orphan*/  AcpiLeaveSleepState (size_t) ; 
 int /*<<< orphan*/  AcpiLeaveSleepStatePrep (size_t) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,size_t,...) ; 

__attribute__((used)) static void
AcpiDbDoOneSleepState (
    UINT8                   SleepState)
{
    ACPI_STATUS             Status;
    UINT8                   SleepTypeA;
    UINT8                   SleepTypeB;


    /* Validate parameter */

    if (SleepState > ACPI_S_STATES_MAX)
    {
        AcpiOsPrintf ("Sleep state %d out of range (%d max)\n",
            SleepState, ACPI_S_STATES_MAX);
        return;
    }

    AcpiOsPrintf ("\n---- Invoking sleep state S%d (%s):\n",
        SleepState, AcpiGbl_SleepStateNames[SleepState]);

    /* Get the values for the sleep type registers (for display only) */

    Status = AcpiGetSleepTypeData (SleepState, &SleepTypeA, &SleepTypeB);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not evaluate [%s] method, %s\n",
            AcpiGbl_SleepStateNames[SleepState],
            AcpiFormatException (Status));
        return;
    }

    AcpiOsPrintf (
        "Register values for sleep state S%d: Sleep-A: %.2X, Sleep-B: %.2X\n",
        SleepState, SleepTypeA, SleepTypeB);

    /* Invoke the various sleep/wake interfaces */

    AcpiOsPrintf ("**** Sleep: Prepare to sleep (S%d) ****\n",
        SleepState);
    Status = AcpiEnterSleepStatePrep (SleepState);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    AcpiOsPrintf ("**** Sleep: Going to sleep (S%d) ****\n",
        SleepState);
    Status = AcpiEnterSleepState (SleepState);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    AcpiOsPrintf ("**** Wake: Prepare to return from sleep (S%d) ****\n",
        SleepState);
    Status = AcpiLeaveSleepStatePrep (SleepState);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    AcpiOsPrintf ("**** Wake: Return from sleep (S%d) ****\n",
        SleepState);
    Status = AcpiLeaveSleepState (SleepState);
    if (ACPI_FAILURE (Status))
    {
        goto ErrorExit;
    }

    return;


ErrorExit:
    ACPI_EXCEPTION ((AE_INFO, Status, "During invocation of sleep state S%d",
        SleepState));
}