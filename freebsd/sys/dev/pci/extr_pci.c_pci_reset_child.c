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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_RESET_POST (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BUS_RESET_PREPARE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUS_RESUME_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BUS_SUSPEND_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DEVF_RESET_DETACH ; 
 scalar_t__ DS_ATTACHED ; 
 int device_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_power_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_flr (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
pci_reset_child(device_t dev, device_t child, int flags)
{
	int error;

	if (dev == NULL || device_get_parent(child) != dev)
		return (0);
	if ((flags & DEVF_RESET_DETACH) != 0) {
		error = device_get_state(child) == DS_ATTACHED ?
		    device_detach(child) : 0;
	} else {
		error = BUS_SUSPEND_CHILD(dev, child);
	}
	if (error == 0) {
		if (!pcie_flr(child, 1000, false)) {
			error = BUS_RESET_PREPARE(dev, child);
			if (error == 0)
				pci_power_reset(child);
			BUS_RESET_POST(dev, child);
		}
		if ((flags & DEVF_RESET_DETACH) != 0)
			device_probe_and_attach(child);
		else
			BUS_RESUME_CHILD(dev, child);
	}
	return (error);
}