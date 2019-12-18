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

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ acpi_device_pwr_for_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  acpi_set_powerstate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_set_power_children(device_t dev, int state)
{
	device_t child;
	device_t *devlist;
	int dstate, i, numdevs;

	if (device_get_children(dev, &devlist, &numdevs) != 0)
		return;

	/*
	 * Retrieve and set D-state for the sleep state if _SxD is present.
	 * Skip children who aren't attached since they are handled separately.
	 */
	for (i = 0; i < numdevs; i++) {
		child = devlist[i];
		dstate = state;
		if (device_is_attached(child) &&
		    acpi_device_pwr_for_sleep(dev, child, &dstate) == 0)
			acpi_set_powerstate(child, dstate);
	}
	free(devlist, M_TEMP);
}