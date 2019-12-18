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
 scalar_t__ PCI_VENDOR_NETLOGIC ; 
 int PIC_PCIE_IRQ (int) ; 
 scalar_t__ pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int xlp_pcie_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips_pcib_route_interrupt(device_t bus, device_t dev, int pin)
{
	int f, d;

	/*
	 * Validate requested pin number.
	 */
	if ((pin < 1) || (pin > 4))
		return (255);

	if (pci_get_bus(dev) == 0 &&
	    pci_get_vendor(dev) == PCI_VENDOR_NETLOGIC) {
		f = pci_get_function(dev);
		d = pci_get_slot(dev) % 8;

		/*
		 * For PCIe links, return link IRT, for other SoC devices
		 * get the IRT from its PCIe header
		 */
		if (d == 1)
			return (PIC_PCIE_IRQ(f));
		else
			return (255);	/* use intline, don't reroute */
	} else {
		/* Regular PCI devices */
		return (PIC_PCIE_IRQ(xlp_pcie_link(bus, dev)));
	}
}