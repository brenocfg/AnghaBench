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
typedef  unsigned char u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct pci_bus {unsigned char number; } ;

/* Variables and functions */
 unsigned char HT1LO_PCICFG_BASE ; 
 unsigned char HT1LO_PCICFG_BASE_TP1 ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned char PCI_ACCESS_WRITE ; 
 int PCI_CFG_SPACE_EXP_SIZE ; 
 int PCI_CFG_SPACE_SIZE ; 
 int PCI_FUNC (unsigned int) ; 
 int PCI_SLOT (unsigned int) ; 
 scalar_t__ TO_UNCAC (unsigned char) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char pci_resource_start (struct pci_dev*,int) ; 
 int readl (void*) ; 
 int /*<<< orphan*/  writel (int,void*) ; 

__attribute__((used)) static int loongson3_pci_config_access(unsigned char access_type,
		struct pci_bus *bus, unsigned int devfn,
		int where, u32 *data)
{
	unsigned char busnum = bus->number;
	int function = PCI_FUNC(devfn);
	int device = PCI_SLOT(devfn);
	int reg = where & ~3;
	void *addrp;
	u64 addr;

	if (where < PCI_CFG_SPACE_SIZE) { /* standard config */
		addr = (busnum << 16) | (device << 11) | (function << 8) | reg;
		if (busnum == 0) {
			if (device > 31)
				return PCIBIOS_DEVICE_NOT_FOUND;
			addrp = (void *)TO_UNCAC(HT1LO_PCICFG_BASE | addr);
		} else {
			addrp = (void *)TO_UNCAC(HT1LO_PCICFG_BASE_TP1 | addr);
		}
	} else if (where < PCI_CFG_SPACE_EXP_SIZE) {  /* extended config */
		struct pci_dev *rootdev;

		rootdev = pci_get_domain_bus_and_slot(0, 0, 0);
		if (!rootdev)
			return PCIBIOS_DEVICE_NOT_FOUND;

		addr = pci_resource_start(rootdev, 3);
		if (!addr)
			return PCIBIOS_DEVICE_NOT_FOUND;

		addr |= busnum << 20 | device << 15 | function << 12 | reg;
		addrp = (void *)TO_UNCAC(addr);
	} else {
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	if (access_type == PCI_ACCESS_WRITE)
		writel(*data, addrp);
	else {
		*data = readl(addrp);
		if (*data == 0xffffffff) {
			*data = -1;
			return PCIBIOS_DEVICE_NOT_FOUND;
		}
	}
	return PCIBIOS_SUCCESSFUL;
}