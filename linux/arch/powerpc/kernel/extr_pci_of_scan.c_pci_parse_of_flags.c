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

/* Variables and functions */
 unsigned int IORESOURCE_IO ; 
 unsigned int IORESOURCE_MEM ; 
 unsigned int IORESOURCE_MEM_64 ; 
 unsigned int IORESOURCE_PREFETCH ; 
 unsigned int IORESOURCE_READONLY ; 
 unsigned int IORESOURCE_SIZEALIGN ; 
 int OF_PCI_ADDR0_ALIAS ; 
 int OF_PCI_ADDR0_BARREG ; 
 int OF_PCI_ADDR0_PREFETCH ; 
 unsigned int OF_PCI_ADDR0_SPACE_IO ; 
 int OF_PCI_ADDR0_SPACE_MASK ; 
 unsigned int OF_PCI_ADDR0_SPACE_MMIO32 ; 
 unsigned int OF_PCI_ADDR0_SPACE_MMIO64 ; 
 unsigned int PCI_BASE_ADDRESS_MEM_PREFETCH ; 
 unsigned int PCI_BASE_ADDRESS_MEM_TYPE_1M ; 
 unsigned int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 unsigned int PCI_BASE_ADDRESS_SPACE_IO ; 
 unsigned int PCI_BASE_ADDRESS_SPACE_MEMORY ; 
 int PCI_ROM_ADDRESS ; 

unsigned int pci_parse_of_flags(u32 addr0, int bridge)
{
	unsigned int flags = 0, as = addr0 & OF_PCI_ADDR0_SPACE_MASK;

	if (as == OF_PCI_ADDR0_SPACE_MMIO32 || as == OF_PCI_ADDR0_SPACE_MMIO64) {
		flags = IORESOURCE_MEM | PCI_BASE_ADDRESS_SPACE_MEMORY;

		if (as == OF_PCI_ADDR0_SPACE_MMIO64)
			flags |= PCI_BASE_ADDRESS_MEM_TYPE_64 | IORESOURCE_MEM_64;

		if (addr0 & OF_PCI_ADDR0_ALIAS)
			flags |= PCI_BASE_ADDRESS_MEM_TYPE_1M;

		if (addr0 & OF_PCI_ADDR0_PREFETCH)
			flags |= IORESOURCE_PREFETCH |
				 PCI_BASE_ADDRESS_MEM_PREFETCH;

		/* Note: We don't know whether the ROM has been left enabled
		 * by the firmware or not. We mark it as disabled (ie, we do
		 * not set the IORESOURCE_ROM_ENABLE flag) for now rather than
		 * do a config space read, it will be force-enabled if needed
		 */
		if (!bridge && (addr0 & OF_PCI_ADDR0_BARREG) == PCI_ROM_ADDRESS)
			flags |= IORESOURCE_READONLY;

	} else if (as == OF_PCI_ADDR0_SPACE_IO)
		flags = IORESOURCE_IO | PCI_BASE_ADDRESS_SPACE_IO;

	if (flags)
		flags |= IORESOURCE_SIZEALIGN;

	return flags;
}