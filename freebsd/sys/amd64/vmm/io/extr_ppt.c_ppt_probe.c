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
struct TYPE_2__ {int hdrtype; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int PCIM_HDRTYPE ; 
 int PCIM_HDRTYPE_NORMAL ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ vmm_is_pptdev (int,int,int) ; 

__attribute__((used)) static int
ppt_probe(device_t dev)
{
	int bus, slot, func;
	struct pci_devinfo *dinfo;

	dinfo = (struct pci_devinfo *)device_get_ivars(dev);

	bus = pci_get_bus(dev);
	slot = pci_get_slot(dev);
	func = pci_get_function(dev);

	/*
	 * To qualify as a pci passthrough device a device must:
	 * - be allowed by administrator to be used in this role
	 * - be an endpoint device
	 */
	if ((dinfo->cfg.hdrtype & PCIM_HDRTYPE) != PCIM_HDRTYPE_NORMAL)
		return (ENXIO);
	else if (vmm_is_pptdev(bus, slot, func))
		return (0);
	else
		/*
		 * Returning BUS_PROBE_NOWILDCARD here matches devices that the
		 * SR-IOV infrastructure specified as "ppt" passthrough devices.
		 * All normal devices that did not have "ppt" specified as their
		 * driver will not be matched by this.
		 */
		return (BUS_PROBE_NOWILDCARD);
}