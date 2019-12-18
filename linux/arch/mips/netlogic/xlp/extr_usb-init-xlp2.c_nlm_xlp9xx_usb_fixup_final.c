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
struct TYPE_2__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; } ;
struct pci_dev {int devfn; void* irq; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  PIC_9XX_XHCI_0_IRQ ; 
 int /*<<< orphan*/  PIC_9XX_XHCI_1_IRQ ; 
 int /*<<< orphan*/  PIC_9XX_XHCI_2_IRQ ; 
 void* nlm_irq_to_xirq (int,int /*<<< orphan*/ ) ; 
 int xlp_socdev_to_node (struct pci_dev*) ; 
 int /*<<< orphan*/  xlp_usb_dmamask ; 

__attribute__((used)) static void nlm_xlp9xx_usb_fixup_final(struct pci_dev *dev)
{
	int node;

	node = xlp_socdev_to_node(dev);
	dev->dev.dma_mask		= &xlp_usb_dmamask;
	dev->dev.coherent_dma_mask	= DMA_BIT_MASK(32);
	switch (dev->devfn) {
	case 0x21:
		dev->irq = nlm_irq_to_xirq(node, PIC_9XX_XHCI_0_IRQ);
		break;
	case 0x22:
		dev->irq = nlm_irq_to_xirq(node, PIC_9XX_XHCI_1_IRQ);
		break;
	case 0x23:
		dev->irq = nlm_irq_to_xirq(node, PIC_9XX_XHCI_2_IRQ);
		break;
	}
}