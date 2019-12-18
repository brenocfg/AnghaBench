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
struct ps3_private {int /*<<< orphan*/  thread_id; int /*<<< orphan*/  ppe_id; int /*<<< orphan*/  ipi_mask; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct ps3_private* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lv1_end_of_interrupt_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ps3_chip_eoi(struct irq_data *d)
{
	const struct ps3_private *pd = irq_data_get_irq_chip_data(d);

	/* non-IPIs are EOIed here. */

	if (!test_bit(63 - d->irq, &pd->ipi_mask))
		lv1_end_of_interrupt_ext(pd->ppe_id, pd->thread_id, d->irq);
}