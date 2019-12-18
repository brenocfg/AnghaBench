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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_2__ {int /*<<< orphan*/  SleepControl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_STATE_S0 ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ACPI_X_SLEEP_ENABLE ; 
 int ACPI_X_SLEEP_TYPE_MASK ; 
 int ACPI_X_SLEEP_TYPE_POSITION ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int AcpiGbl_SleepTypeA ; 
 int /*<<< orphan*/  AcpiGbl_SleepTypeB ; 
 int /*<<< orphan*/  AcpiGetSleepTypeData (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HwExtendedWakePrep ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiHwExtendedWakePrep (
    UINT8                   SleepState)
{
    ACPI_STATUS             Status;
    UINT8                   SleepTypeValue;


    ACPI_FUNCTION_TRACE (HwExtendedWakePrep);


    Status = AcpiGetSleepTypeData (ACPI_STATE_S0,
        &AcpiGbl_SleepTypeA, &AcpiGbl_SleepTypeB);
    if (ACPI_SUCCESS (Status))
    {
        SleepTypeValue = ((AcpiGbl_SleepTypeA << ACPI_X_SLEEP_TYPE_POSITION) &
            ACPI_X_SLEEP_TYPE_MASK);

        (void) AcpiWrite ((UINT64) (SleepTypeValue | ACPI_X_SLEEP_ENABLE),
            &AcpiGbl_FADT.SleepControl);
    }

    return_ACPI_STATUS (AE_OK);
}