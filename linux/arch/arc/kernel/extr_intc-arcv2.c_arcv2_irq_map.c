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
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ FIRST_EXT_IRQ ; 
 int /*<<< orphan*/  arcv2_irq_chip ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_percpu_devid (unsigned int) ; 

__attribute__((used)) static int arcv2_irq_map(struct irq_domain *d, unsigned int irq,
			 irq_hw_number_t hw)
{
	/*
	 * core intc IRQs [16, 23]:
	 * Statically assigned always private-per-core (Timers, WDT, IPI, PCT)
	 */
	if (hw < FIRST_EXT_IRQ) {
		/*
		 * A subsequent request_percpu_irq() fails if percpu_devid is
		 * not set. That in turns sets NOAUTOEN, meaning each core needs
		 * to call enable_percpu_irq()
		 */
		irq_set_percpu_devid(irq);
		irq_set_chip_and_handler(irq, &arcv2_irq_chip, handle_percpu_irq);
	} else {
		irq_set_chip_and_handler(irq, &arcv2_irq_chip, handle_level_irq);
	}

	return 0;
}