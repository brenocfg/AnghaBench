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
struct pci_dev {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 size_t PCI_FUNC (int /*<<< orphan*/ ) ; 
 int* internal_func_irqs ; 
 int* irq_tab_mpc30x ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	if (slot == 30)
		return internal_func_irqs[PCI_FUNC(dev->devfn)];

	return irq_tab_mpc30x[slot];
}