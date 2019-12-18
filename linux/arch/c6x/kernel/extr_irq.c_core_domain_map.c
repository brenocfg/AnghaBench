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
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IRQ_LEVEL ; 
 int NR_PRIORITY_IRQS ; 
 int /*<<< orphan*/  core_chip ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int* prio_to_virq ; 

__attribute__((used)) static int core_domain_map(struct irq_domain *h, unsigned int virq,
			   irq_hw_number_t hw)
{
	if (hw < 4 || hw >= NR_PRIORITY_IRQS)
		return -EINVAL;

	prio_to_virq[hw] = virq;

	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &core_chip, handle_level_irq);
	return 0;
}