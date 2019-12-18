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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/  (*) (char*)) ; 
 scalar_t__ ACPI_S_STATES_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDbDoOneSleepState (scalar_t__) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDbSleep (
    char                    *ObjectArg)
{
    UINT8                   SleepState;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (AcpiDbSleep);


    /* Null input (no arguments) means to invoke all sleep states */

    if (!ObjectArg)
    {
        AcpiOsPrintf ("Invoking all possible sleep states, 0-%d\n",
            ACPI_S_STATES_MAX);

        for (i = 0; i <= ACPI_S_STATES_MAX; i++)
        {
            AcpiDbDoOneSleepState ((UINT8) i);
        }

        return_ACPI_STATUS (AE_OK);
    }

    /* Convert argument to binary and invoke the sleep state */

    SleepState = (UINT8) strtoul (ObjectArg, NULL, 0);
    AcpiDbDoOneSleepState (SleepState);
    return_ACPI_STATUS (AE_OK);
}