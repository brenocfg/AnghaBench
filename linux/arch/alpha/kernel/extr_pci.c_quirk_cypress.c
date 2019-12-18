#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_iommu_arena {int dma_base; int size; } ;
struct pci_dev {int class; struct pci_controller* sysdata; TYPE_1__* resource; int /*<<< orphan*/  devfn; } ;
struct pci_controller {struct pci_iommu_arena* sg_pci; } ;
struct TYPE_2__ {int start; int end; scalar_t__ flags; } ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_ISA ; 
 int PCI_CLASS_STORAGE_IDE ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int __direct_map_base ; 
 int __direct_map_size ; 

__attribute__((used)) static void quirk_cypress(struct pci_dev *dev)
{
	/* The Notorious Cy82C693 chip.  */

	/* The generic legacy mode IDE fixup in drivers/pci/probe.c
	   doesn't work correctly with the Cypress IDE controller as
	   it has non-standard register layout.  Fix that.  */
	if (dev->class >> 8 == PCI_CLASS_STORAGE_IDE) {
		dev->resource[2].start = dev->resource[3].start = 0;
		dev->resource[2].end = dev->resource[3].end = 0;
		dev->resource[2].flags = dev->resource[3].flags = 0;
		if (PCI_FUNC(dev->devfn) == 2) {
			dev->resource[0].start = 0x170;
			dev->resource[0].end = 0x177;
			dev->resource[1].start = 0x376;
			dev->resource[1].end = 0x376;
		}
	}

	/* The Cypress bridge responds on the PCI bus in the address range
	   0xffff0000-0xffffffff (conventional x86 BIOS ROM).  There is no
	   way to turn this off.  The bridge also supports several extended
	   BIOS ranges (disabled after power-up), and some consoles do turn
	   them on.  So if we use a large direct-map window, or a large SG
	   window, we must avoid the entire 0xfff00000-0xffffffff region.  */
	if (dev->class >> 8 == PCI_CLASS_BRIDGE_ISA) {
		if (__direct_map_base + __direct_map_size >= 0xfff00000UL)
			__direct_map_size = 0xfff00000UL - __direct_map_base;
		else {
			struct pci_controller *hose = dev->sysdata;
			struct pci_iommu_arena *pci = hose->sg_pci;
			if (pci && pci->dma_base + pci->size >= 0xfff00000UL)
				pci->size = 0xfff00000UL - pci->dma_base;
		}
	}
}