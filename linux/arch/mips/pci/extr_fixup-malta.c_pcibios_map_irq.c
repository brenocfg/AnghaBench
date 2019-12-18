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
typedef  size_t u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int** irq_tab ; 
 int* pci_irq ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	int virq;
	virq = irq_tab[slot][pin];
	return pci_irq[virq];
}