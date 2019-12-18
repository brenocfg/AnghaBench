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
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  chip_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_MOVE_PCNTXT ; 
 int /*<<< orphan*/  IRQ_NO_BALANCING ; 
 int /*<<< orphan*/  irq_clear_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_top (struct irq_domain*,unsigned int,unsigned int) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv_domain_free(struct irq_domain *domain, unsigned int virq,
			   unsigned int nr_irqs)
{
	struct irq_data *irq_data = irq_domain_get_irq_data(domain, virq);

	BUG_ON(nr_irqs != 1);
	kfree(irq_data->chip_data);
	irq_clear_status_flags(virq, IRQ_MOVE_PCNTXT);
	irq_clear_status_flags(virq, IRQ_NO_BALANCING);
	irq_domain_free_irqs_top(domain, virq, nr_irqs);
}