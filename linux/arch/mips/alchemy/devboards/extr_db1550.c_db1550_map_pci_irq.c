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
 int AU1550_PCI_INTA ; 
 int AU1550_PCI_INTB ; 
 int AU1550_PCI_INTC ; 
 int AU1550_PCI_INTD ; 

__attribute__((used)) static int db1550_map_pci_irq(const struct pci_dev *d, u8 slot, u8 pin)
{
	if ((slot < 11) || (slot > 13) || pin == 0)
		return -1;
	if (slot == 11)
		return (pin == 1) ? AU1550_PCI_INTC : 0xff;
	if (slot == 12) {
		switch (pin) {
		case 1: return AU1550_PCI_INTB;
		case 2: return AU1550_PCI_INTC;
		case 3: return AU1550_PCI_INTD;
		case 4: return AU1550_PCI_INTA;
		}
	}
	if (slot == 13) {
		switch (pin) {
		case 1: return AU1550_PCI_INTA;
		case 2: return AU1550_PCI_INTB;
		case 3: return AU1550_PCI_INTC;
		case 4: return AU1550_PCI_INTD;
		}
	}
	return -1;
}