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
 int BUS_PROBE_GENERIC ; 
 int ENXIO ; 
 scalar_t__ PCIC_BRIDGE ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ebus_pci_probe(device_t dev)
{

	if (pci_get_class(dev) != PCIC_BRIDGE ||
	    pci_get_vendor(dev) != 0x108e ||
	    strcmp(ofw_bus_get_name(dev), "ebus") != 0)
		return (ENXIO);

	if (pci_get_device(dev) == 0x1000)
		device_set_desc(dev, "PCI-EBus2 bridge");
	else if (pci_get_device(dev) == 0x1100)
		device_set_desc(dev, "PCI-EBus3 bridge");
	else
		return (ENXIO);
	return (BUS_PROBE_GENERIC);
}