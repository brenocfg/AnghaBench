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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_HOST ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_hostb_probe(device_t dev)
{
	u_int32_t id;

	id = pci_get_devid(dev);

	switch (id) {

	/* VIA VT82C596 Power Management Function */
	case 0x30501106:
		return (ENXIO);

	default:
		break;
	}

	if (pci_get_class(dev) == PCIC_BRIDGE &&
	    pci_get_subclass(dev) == PCIS_BRIDGE_HOST) {
		device_set_desc(dev, "Host to PCI bridge");
		device_quiet(dev);
		return (-10000);
	}
	return (ENXIO);
}