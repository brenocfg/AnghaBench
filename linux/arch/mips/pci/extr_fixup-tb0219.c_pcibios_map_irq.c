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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int TB0219_PCI_SLOT1_IRQ ; 
 int TB0219_PCI_SLOT2_IRQ ; 
 int TB0219_PCI_SLOT3_IRQ ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	int irq = -1;

	switch (slot) {
	case 12:
		irq = TB0219_PCI_SLOT1_IRQ;
		break;
	case 13:
		irq = TB0219_PCI_SLOT2_IRQ;
		break;
	case 14:
		irq = TB0219_PCI_SLOT3_IRQ;
		break;
	default:
		break;
	}

	return irq;
}