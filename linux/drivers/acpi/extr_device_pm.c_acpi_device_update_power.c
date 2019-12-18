#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ power_resources; } ;
struct TYPE_4__ {int state; TYPE_1__ flags; } ;
struct acpi_device {TYPE_2__ power; } ;

/* Variables and functions */
 int ACPI_STATE_D0 ; 
 int ACPI_STATE_UNKNOWN ; 
 int acpi_bus_init_power (struct acpi_device*) ; 
 int acpi_device_get_power (struct acpi_device*,int*) ; 
 int acpi_device_set_power (struct acpi_device*,int) ; 
 int acpi_power_transition (struct acpi_device*,int) ; 

int acpi_device_update_power(struct acpi_device *device, int *state_p)
{
	int state;
	int result;

	if (device->power.state == ACPI_STATE_UNKNOWN) {
		result = acpi_bus_init_power(device);
		if (!result && state_p)
			*state_p = device->power.state;

		return result;
	}

	result = acpi_device_get_power(device, &state);
	if (result)
		return result;

	if (state == ACPI_STATE_UNKNOWN) {
		state = ACPI_STATE_D0;
		result = acpi_device_set_power(device, state);
		if (result)
			return result;
	} else {
		if (device->power.flags.power_resources) {
			/*
			 * We don't need to really switch the state, bu we need
			 * to update the power resources' reference counters.
			 */
			result = acpi_power_transition(device, state);
			if (result)
				return result;
		}
		device->power.state = state;
	}
	if (state_p)
		*state_p = state;

	return 0;
}