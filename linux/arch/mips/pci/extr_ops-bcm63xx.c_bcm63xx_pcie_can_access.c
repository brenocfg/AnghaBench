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
struct pci_bus {int number; } ;

/* Variables and functions */
 int DLSTATUS_PHYLINKUP ; 
#define  PCIE_BUS_BRIDGE 129 
#define  PCIE_BUS_DEVICE 128 
 int /*<<< orphan*/  PCIE_DLSTATUS_REG ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int bcm_pcie_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm63xx_pcie_can_access(struct pci_bus *bus, int devfn)
{
	switch (bus->number) {
	case PCIE_BUS_BRIDGE:
		return PCI_SLOT(devfn) == 0;
	case PCIE_BUS_DEVICE:
		if (PCI_SLOT(devfn) == 0)
			return bcm_pcie_readl(PCIE_DLSTATUS_REG)
					& DLSTATUS_PHYLINKUP;
		/* else, fall through */
	default:
		return false;
	}
}