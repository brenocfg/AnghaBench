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
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct pci_devinfo {int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_POWERSTATE_D3 ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int bus_generic_suspend_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_suspend_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_save (int /*<<< orphan*/ ,struct pci_devinfo*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_do_power_suspend ; 
 int /*<<< orphan*/  pci_set_power_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pci_suspend_child(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo;
	struct resource_list_entry *rle;
	int error;

	dinfo = device_get_ivars(child);

	/*
	 * Save the PCI configuration space for the child and set the
	 * device in the appropriate power state for this sleep state.
	 */
	pci_cfg_save(child, dinfo, 0);

	/* Suspend devices before potentially powering them down. */
	error = bus_generic_suspend_child(dev, child);

	if (error)
		return (error);

	if (pci_do_power_suspend) {
		/*
		 * Make sure this device's interrupt handler is not invoked
		 * in the case the device uses a shared interrupt that can
		 * be raised by some other device.
		 * This is applicable only to regular (legacy) PCI interrupts
		 * as MSI/MSI-X interrupts are never shared.
		 */
		rle = resource_list_find(&dinfo->resources,
		    SYS_RES_IRQ, 0);
		if (rle != NULL && rle->res != NULL)
			(void)bus_suspend_intr(child, rle->res);
		pci_set_power_child(dev, child, PCI_POWERSTATE_D3);
	}

	return (0);
}