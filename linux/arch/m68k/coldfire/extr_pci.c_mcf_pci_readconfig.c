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
struct pci_bus {scalar_t__ number; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 unsigned long PCICAR ; 
 unsigned long PCICAR_E ; 
 size_t PCI_SLOT (unsigned int) ; 
 int __raw_readb (unsigned long) ; 
 int /*<<< orphan*/  __raw_readl (unsigned long) ; 
 int /*<<< orphan*/  __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,unsigned long) ; 
 int iospace ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__* mcf_host_slot2sid ; 
 unsigned long mcf_mk_pcicar (scalar_t__,unsigned int,int) ; 

__attribute__((used)) static int mcf_pci_readconfig(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 *value)
{
	unsigned long addr;

	*value = 0xffffffff;

	if (bus->number == 0) {
		if (mcf_host_slot2sid[PCI_SLOT(devfn)] == 0)
			return PCIBIOS_SUCCESSFUL;
	}

	addr = mcf_mk_pcicar(bus->number, devfn, where);
	__raw_writel(PCICAR_E | addr, PCICAR);
	__raw_readl(PCICAR);
	addr = iospace + (where & 0x3);

	switch (size) {
	case 1:
		*value = __raw_readb(addr);
		break;
	case 2:
		*value = le16_to_cpu(__raw_readw(addr));
		break;
	default:
		*value = le32_to_cpu(__raw_readl(addr));
		break;
	}

	__raw_writel(0, PCICAR);
	__raw_readl(PCICAR);
	return PCIBIOS_SUCCESSFUL;
}