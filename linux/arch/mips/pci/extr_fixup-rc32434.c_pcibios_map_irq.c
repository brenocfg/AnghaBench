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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int GROUP4_IRQ_BASE ; 
 size_t PCI_SLOT (int /*<<< orphan*/ ) ; 
 int** irq_map ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	int irq = 0;

	if (dev->bus->number < 2 && PCI_SLOT(dev->devfn) < 12)
		irq = irq_map[dev->bus->number][PCI_SLOT(dev->devfn)];

	return irq + GROUP4_IRQ_BASE + 4;
}