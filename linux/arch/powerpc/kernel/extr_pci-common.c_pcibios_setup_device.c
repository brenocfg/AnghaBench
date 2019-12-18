#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dma_offset; } ;
struct TYPE_8__ {TYPE_2__ archdata; } ;
struct pci_dev {int /*<<< orphan*/  bus; TYPE_3__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* dma_dev_setup ) (struct pci_dev*) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* pci_irq_fixup ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DRAM_OFFSET ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_ops ; 
 int /*<<< orphan*/  pci_read_irq_line (struct pci_dev*) ; 
 int /*<<< orphan*/  pcibus_to_node (int /*<<< orphan*/ ) ; 
 TYPE_5__ ppc_md ; 
 int /*<<< orphan*/  set_dev_node (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_ops (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 
 int /*<<< orphan*/  stub2 (struct pci_dev*) ; 

__attribute__((used)) static void pcibios_setup_device(struct pci_dev *dev)
{
	struct pci_controller *phb;
	/* Fixup NUMA node as it may not be setup yet by the generic
	 * code and is needed by the DMA init
	 */
	set_dev_node(&dev->dev, pcibus_to_node(dev->bus));

	/* Hook up default DMA ops */
	set_dma_ops(&dev->dev, pci_dma_ops);
	dev->dev.archdata.dma_offset = PCI_DRAM_OFFSET;

	/* Additional platform DMA/iommu setup */
	phb = pci_bus_to_host(dev->bus);
	if (phb->controller_ops.dma_dev_setup)
		phb->controller_ops.dma_dev_setup(dev);

	/* Read default IRQs and fixup if necessary */
	pci_read_irq_line(dev);
	if (ppc_md.pci_irq_fixup)
		ppc_md.pci_irq_fixup(dev);
}