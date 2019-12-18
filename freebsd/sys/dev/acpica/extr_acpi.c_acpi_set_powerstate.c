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
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int ACPI_D_STATES_MAX ; 
 int ACPI_STATE_D0 ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ AE_NOT_FOUND ; 
 int /*<<< orphan*/  AcpiFormatException (scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_name (int /*<<< orphan*/ *) ; 
 scalar_t__ acpi_pwr_switch_consumer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
acpi_set_powerstate(device_t child, int state)
{
    ACPI_HANDLE h;
    ACPI_STATUS status;

    h = acpi_get_handle(child);
    if (state < ACPI_STATE_D0 || state > ACPI_D_STATES_MAX)
	return (EINVAL);
    if (h == NULL)
	return (0);

    /* Ignore errors if the power methods aren't present. */
    status = acpi_pwr_switch_consumer(h, state);
    if (ACPI_SUCCESS(status)) {
	if (bootverbose)
	    device_printf(child, "set ACPI power state D%d on %s\n",
		state, acpi_name(h));
    } else if (status != AE_NOT_FOUND)
	device_printf(child,
	    "failed to set ACPI power state D%d on %s: %s\n", state,
	    acpi_name(h), AcpiFormatException(status));

    return (0);
}