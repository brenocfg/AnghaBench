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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpic_mask_irq (struct irq_data*) ; 
 int /*<<< orphan*/  pci_msi_mask_irq (struct irq_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpic_pasemi_msi_mask_irq(struct irq_data *data)
{
	pr_debug("mpic_pasemi_msi_mask_irq %d\n", data->irq);
	pci_msi_mask_irq(data);
	mpic_mask_irq(data);
}