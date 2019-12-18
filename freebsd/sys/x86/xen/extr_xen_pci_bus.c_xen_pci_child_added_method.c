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
struct physdev_pci_device_add {int devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  seg; } ;
struct TYPE_2__ {int slot; int func; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  add_pci ;

/* Variables and functions */
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_pci_device_add*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PHYSDEVOP_pci_device_add ; 
 int /*<<< orphan*/  bzero (struct physdev_pci_device_add*,int) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int,int) ; 

void
xen_pci_child_added_method(device_t dev, device_t child)
{
	struct pci_devinfo *dinfo;
	struct physdev_pci_device_add add_pci;
	int error;

	dinfo = device_get_ivars(child);
	KASSERT((dinfo != NULL),
	    ("xen_pci_add_child_method called with NULL dinfo"));

	bzero(&add_pci, sizeof(add_pci));
	add_pci.seg = dinfo->cfg.domain;
	add_pci.bus = dinfo->cfg.bus;
	add_pci.devfn = (dinfo->cfg.slot << 3) | dinfo->cfg.func;
	error = HYPERVISOR_physdev_op(PHYSDEVOP_pci_device_add, &add_pci);
	if (error)
		panic("unable to add device bus %u devfn %u error: %d\n",
		    add_pci.bus, add_pci.devfn, error);
}