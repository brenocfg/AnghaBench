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
struct pci_devinfo {int /*<<< orphan*/  cfg; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_IDENTIFY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DS_NOTPRESENT ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_restore (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_child_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_print_verbose (struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_printf (int /*<<< orphan*/ *,char*) ; 

void
pci_driver_added(device_t dev, driver_t *driver)
{
	int numdevs;
	device_t *devlist;
	device_t child;
	struct pci_devinfo *dinfo;
	int i;

	if (bootverbose)
		device_printf(dev, "driver added\n");
	DEVICE_IDENTIFY(driver, dev);
	if (device_get_children(dev, &devlist, &numdevs) != 0)
		return;
	for (i = 0; i < numdevs; i++) {
		child = devlist[i];
		if (device_get_state(child) != DS_NOTPRESENT)
			continue;
		dinfo = device_get_ivars(child);
		pci_print_verbose(dinfo);
		if (bootverbose)
			pci_printf(&dinfo->cfg, "reprobing on driver added\n");
		pci_cfg_restore(child, dinfo);
		if (device_probe_and_attach(child) != 0)
			pci_child_detached(dev, child);
	}
	free(devlist, M_TEMP);
}