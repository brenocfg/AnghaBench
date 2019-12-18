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
struct pci_link {int pl_irqmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_INTERRUPT_VALID (int) ; 

__attribute__((used)) static int
pci_pir_valid_irq(struct pci_link *pci_link, int irq)
{

	if (!PCI_INTERRUPT_VALID(irq))
		return (0);
	return (pci_link->pl_irqmask & (1 << irq));
}