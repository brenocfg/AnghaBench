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
typedef  unsigned char u8 ;
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 unsigned char JMR3927_IRQ_ETHER0 ; 
 unsigned char JMR3927_IRQ_IOC_PCIA ; 
 unsigned char JMR3927_IRQ_IOC_PCIB ; 
 unsigned char JMR3927_IRQ_IOC_PCIC ; 
 unsigned char JMR3927_IRQ_IOC_PCID ; 
 unsigned char TX3927_PCIC_IDSEL_AD_TO_SLOT (int) ; 
 int TXX9_PCI_OPT_PICMG ; 
 int txx9_pci_option ; 

int jmr3927_pci_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	unsigned char irq = pin;

	/* IRQ rotation (PICMG) */
	irq--;			/* 0-3 */
	if (slot == TX3927_PCIC_IDSEL_AD_TO_SLOT(23)) {
		/* PCI CardSlot (IDSEL=A23, DevNu=12) */
		/* PCIA => PCIC (IDSEL=A23) */
		/* NOTE: JMR3927 JP1 must be set to OPEN */
		irq = (irq + 2) % 4;
	} else if (slot == TX3927_PCIC_IDSEL_AD_TO_SLOT(22)) {
		/* PCI CardSlot (IDSEL=A22, DevNu=11) */
		/* PCIA => PCIA (IDSEL=A22) */
		/* NOTE: JMR3927 JP1 must be set to OPEN */
		irq = (irq + 0) % 4;
	} else {
		/* PCI Backplane */
		if (txx9_pci_option & TXX9_PCI_OPT_PICMG)
			irq = (irq + 33 - slot) % 4;
		else
			irq = (irq + 3 + slot) % 4;
	}
	irq++;			/* 1-4 */

	switch (irq) {
	case 1:
		irq = JMR3927_IRQ_IOC_PCIA;
		break;
	case 2:
		irq = JMR3927_IRQ_IOC_PCIB;
		break;
	case 3:
		irq = JMR3927_IRQ_IOC_PCIC;
		break;
	case 4:
		irq = JMR3927_IRQ_IOC_PCID;
		break;
	}

	/* Check OnBoard Ethernet (IDSEL=A24, DevNu=13) */
	if (dev->bus->parent == NULL &&
	    slot == TX3927_PCIC_IDSEL_AD_TO_SLOT(24))
		irq = JMR3927_IRQ_ETHER0;
	return irq;
}