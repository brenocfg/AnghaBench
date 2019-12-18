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
typedef  int u32 ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORION5X_PCIE_WA_VIRT_BASE ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int /*<<< orphan*/  PCI_SLOT (int) ; 
 int orion_pcie_rd_conf_wa (int /*<<< orphan*/ ,struct pci_bus*,int,int,int,int*) ; 
 scalar_t__ pcie_valid_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcie_rd_conf_wa(struct pci_bus *bus, u32 devfn,
			   int where, int size, u32 *val)
{
	int ret;

	if (pcie_valid_config(bus->number, PCI_SLOT(devfn)) == 0) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	/*
	 * We only support access to the non-extended configuration
	 * space when using the WA access method (or we would have to
	 * sacrifice 256M of CPU virtual address space.)
	 */
	if (where >= 0x100) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	ret = orion_pcie_rd_conf_wa(ORION5X_PCIE_WA_VIRT_BASE,
				    bus, devfn, where, size, val);

	return ret;
}