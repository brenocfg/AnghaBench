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
 int /*<<< orphan*/  PCI_POWERSTATE_D0 ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_generic_resume_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_resume_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_restore (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_cfg_save (int /*<<< orphan*/ ,struct pci_devinfo*,int) ; 
 scalar_t__ pci_do_power_resume ; 
 scalar_t__ pci_do_power_suspend ; 
 int /*<<< orphan*/  pci_set_power_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pci_resume_child(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo;
	struct resource_list_entry *rle;

	if (pci_do_power_resume)
		pci_set_power_child(dev, child, PCI_POWERSTATE_D0);

	dinfo = device_get_ivars(child);
	pci_cfg_restore(child, dinfo);
	if (!device_is_attached(child))
		pci_cfg_save(child, dinfo, 1);

	bus_generic_resume_child(dev, child);

	/*
	 * Allow interrupts only after fully resuming the driver and hardware.
	 */
	if (pci_do_power_suspend) {
		/* See pci_suspend_child for details. */
		rle = resource_list_find(&dinfo->resources, SYS_RES_IRQ, 0);
		if (rle != NULL && rle->res != NULL)
			(void)bus_resume_intr(child, rle->res);
	}

	return (0);
}