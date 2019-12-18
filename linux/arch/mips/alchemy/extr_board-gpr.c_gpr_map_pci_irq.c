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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int AU1550_PCI_INTA ; 
 int AU1550_PCI_INTB ; 

__attribute__((used)) static int gpr_map_pci_irq(const struct pci_dev *d, u8 slot, u8 pin)
{
	if ((slot == 0) && (pin == 1))
		return AU1550_PCI_INTA;
	else if ((slot == 0) && (pin == 2))
		return AU1550_PCI_INTB;

	return 0xff;
}