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
 scalar_t__ PCIB_POWER_FOR_SLEEP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_powerstate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_set_power_child(device_t dev, device_t child, int state)
{
	device_t pcib;
	int dstate;

	/*
	 * Set the device to the given state.  If the firmware suggests
	 * a different power state, use it instead.  If power management
	 * is not present, the firmware is responsible for managing
	 * device power.  Skip children who aren't attached since they
	 * are handled separately.
	 */
	pcib = device_get_parent(dev);
	dstate = state;
	if (device_is_attached(child) &&
	    PCIB_POWER_FOR_SLEEP(pcib, child, &dstate) == 0)
		pci_set_powerstate(child, dstate);
}