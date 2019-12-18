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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_STATE_D0 ; 
 int /*<<< orphan*/  ACPI_STATE_D3 ; 
 int /*<<< orphan*/  DEVICE_IDENTIFY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DS_NOTPRESENT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  acpi_set_powerstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ ) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_driver_added(device_t dev, driver_t *driver)
{
    device_t child, *devlist;
    int i, numdevs;

    DEVICE_IDENTIFY(driver, dev);
    if (device_get_children(dev, &devlist, &numdevs))
	    return;
    for (i = 0; i < numdevs; i++) {
	child = devlist[i];
	if (device_get_state(child) == DS_NOTPRESENT) {
#ifdef ACPI_ENABLE_POWERDOWN_NODRIVER
	    acpi_set_powerstate(child, ACPI_STATE_D0);
	    if (device_probe_and_attach(child) != 0)
		acpi_set_powerstate(child, ACPI_STATE_D3);
#else
	    device_probe_and_attach(child);
#endif
	}
    }
    free(devlist, M_TEMP);
}