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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct hub_irq_data {int /*<<< orphan*/ * irq_mask; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writeq (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 struct hub_irq_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_enable_mask ; 
 unsigned long* per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_hub_irq(struct irq_data *d)
{
	struct hub_irq_data *hd = irq_data_get_irq_chip_data(d);
	unsigned long *mask = per_cpu(irq_enable_mask, hd->cpu);

	clear_bit(d->hwirq, mask);
	__raw_writeq(mask[0], hd->irq_mask[0]);
	__raw_writeq(mask[1], hd->irq_mask[1]);
}