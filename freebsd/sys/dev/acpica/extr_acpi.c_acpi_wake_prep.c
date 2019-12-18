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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AcpiGbl_SystemAwakeAndRunning ; 
 int /*<<< orphan*/  acpi_wake_run_prep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_wake_sleep_prep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ACPI_STATUS
acpi_wake_prep(ACPI_HANDLE handle, UINT32 level, void *context, void **status)
{
    int sstate;

    /* If suspending, run the sleep prep function, otherwise wake. */
    sstate = *(int *)context;
    if (AcpiGbl_SystemAwakeAndRunning)
	acpi_wake_sleep_prep(handle, sstate);
    else
	acpi_wake_run_prep(handle, sstate);
    return (AE_OK);
}