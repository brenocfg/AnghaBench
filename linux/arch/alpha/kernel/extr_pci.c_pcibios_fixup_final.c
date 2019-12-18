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
struct pci_dev {int class; scalar_t__ dma_mask; } ;

/* Variables and functions */
 scalar_t__ MAX_ISA_DMA_ADDRESS ; 
 unsigned int PCI_CLASS_BRIDGE_EISA ; 
 unsigned int PCI_CLASS_BRIDGE_ISA ; 
 struct pci_dev* isa_bridge ; 

__attribute__((used)) static void pcibios_fixup_final(struct pci_dev *dev)
{
	unsigned int class = dev->class >> 8;

	if (class == PCI_CLASS_BRIDGE_ISA || class == PCI_CLASS_BRIDGE_EISA) {
		dev->dma_mask = MAX_ISA_DMA_ADDRESS - 1;
		isa_bridge = dev;
	}
}