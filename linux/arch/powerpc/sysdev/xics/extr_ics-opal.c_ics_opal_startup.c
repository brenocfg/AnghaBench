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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ics_opal_unmask_irq (struct irq_data*) ; 
 scalar_t__ irq_data_get_msi_desc (struct irq_data*) ; 
 int /*<<< orphan*/  pci_msi_unmask_irq (struct irq_data*) ; 

__attribute__((used)) static unsigned int ics_opal_startup(struct irq_data *d)
{
#ifdef CONFIG_PCI_MSI
	/*
	 * The generic MSI code returns with the interrupt disabled on the
	 * card, using the MSI mask bits. Firmware doesn't appear to unmask
	 * at that level, so we do it here by hand.
	 */
	if (irq_data_get_msi_desc(d))
		pci_msi_unmask_irq(d);
#endif

	/* unmask it */
	ics_opal_unmask_irq(d);
	return 0;
}