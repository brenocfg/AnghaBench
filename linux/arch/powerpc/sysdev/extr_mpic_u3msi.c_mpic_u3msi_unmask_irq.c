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
 int /*<<< orphan*/  mpic_unmask_irq (struct irq_data*) ; 
 int /*<<< orphan*/  pci_msi_unmask_irq (struct irq_data*) ; 

__attribute__((used)) static void mpic_u3msi_unmask_irq(struct irq_data *data)
{
	mpic_unmask_irq(data);
	pci_msi_unmask_irq(data);
}