#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pci_devinfo {TYPE_1__ cfg; int /*<<< orphan*/  resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_add_child_clear_aer (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_add_device ; 
 int /*<<< orphan*/  pci_add_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_restore (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  pci_cfg_save (int /*<<< orphan*/ ,struct pci_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_child_added (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_clear_aer_on_attach ; 
 int /*<<< orphan*/  pci_print_verbose (struct pci_devinfo*) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

void
pci_add_child(device_t bus, struct pci_devinfo *dinfo)
{
	device_t dev;

	dinfo->cfg.dev = dev = device_add_child(bus, NULL, -1);
	device_set_ivars(dev, dinfo);
	resource_list_init(&dinfo->resources);
	pci_cfg_save(dev, dinfo, 0);
	pci_cfg_restore(dev, dinfo);
	pci_print_verbose(dinfo);
	pci_add_resources(bus, dev, 0, 0);
	pci_child_added(dinfo->cfg.dev);

	if (pci_clear_aer_on_attach)
		pci_add_child_clear_aer(dev, dinfo);

	EVENTHANDLER_INVOKE(pci_add_device, dinfo->cfg.dev);
}