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
struct pci_dev {int devfn; int /*<<< orphan*/  irq; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  PIC_EHCI_0_IRQ ; 
 int /*<<< orphan*/  PIC_EHCI_1_IRQ ; 
 int /*<<< orphan*/  PIC_OHCI_0_IRQ ; 
 int /*<<< orphan*/  PIC_OHCI_1_IRQ ; 
 int /*<<< orphan*/  PIC_OHCI_2_IRQ ; 
 int /*<<< orphan*/  PIC_OHCI_3_IRQ ; 
 int /*<<< orphan*/  xlp_usb_dmamask ; 

__attribute__((used)) static void nlm_usb_fixup_final(struct pci_dev *dev)
{
	dev->dev.dma_mask		= &xlp_usb_dmamask;
	dev->dev.coherent_dma_mask	= DMA_BIT_MASK(32);
	switch (dev->devfn) {
	case 0x10:
		dev->irq = PIC_EHCI_0_IRQ;
		break;
	case 0x11:
		dev->irq = PIC_OHCI_0_IRQ;
		break;
	case 0x12:
		dev->irq = PIC_OHCI_1_IRQ;
		break;
	case 0x13:
		dev->irq = PIC_EHCI_1_IRQ;
		break;
	case 0x14:
		dev->irq = PIC_OHCI_2_IRQ;
		break;
	case 0x15:
		dev->irq = PIC_OHCI_3_IRQ;
		break;
	}
}