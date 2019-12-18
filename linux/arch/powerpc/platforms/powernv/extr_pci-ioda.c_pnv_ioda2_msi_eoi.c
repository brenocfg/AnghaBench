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
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icp_native_eoi (struct irq_data*) ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  pnv_opal_pci_msi_eoi (struct irq_chip*,unsigned int) ; 

__attribute__((used)) static void pnv_ioda2_msi_eoi(struct irq_data *d)
{
	int64_t rc;
	unsigned int hw_irq = (unsigned int)irqd_to_hwirq(d);
	struct irq_chip *chip = irq_data_get_irq_chip(d);

	rc = pnv_opal_pci_msi_eoi(chip, hw_irq);
	WARN_ON_ONCE(rc);

	icp_native_eoi(d);
}