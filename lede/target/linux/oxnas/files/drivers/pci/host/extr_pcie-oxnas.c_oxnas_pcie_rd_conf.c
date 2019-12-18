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
struct pci_bus {int /*<<< orphan*/  number; int /*<<< orphan*/  sysdata; } ;
struct oxnas_pcie {scalar_t__ cfgbase; int /*<<< orphan*/  haslink; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCI_SLOT (int) ; 
 unsigned int oxnas_pcie_cfg_to_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 struct oxnas_pcie* sys_to_pcie (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oxnas_pcie_rd_conf(struct pci_bus *bus, u32 devfn, int where,
			      int size, u32 *val)
{
	struct oxnas_pcie *pcie = sys_to_pcie(bus->sysdata);
	unsigned offset;
	u32 value;
	u32 left_bytes, right_bytes;

	/* Only a single device per bus for PCIe point-to-point links */
	if (PCI_SLOT(devfn) > 0) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	if (!pcie->haslink) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	offset = oxnas_pcie_cfg_to_offset(bus->sysdata, bus->number, devfn,
					  where);
	value = readl_relaxed(pcie->cfgbase + offset);
	left_bytes = where & 3;
	right_bytes = 4 - left_bytes - size;
	value <<= right_bytes * 8;
	value >>= (left_bytes + right_bytes) * 8;
	*val = value;

	return PCIBIOS_SUCCESSFUL;
}