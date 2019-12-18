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

/* Variables and functions */
 int CPU_IRQ_BASE ; 
 int CPU_IRQ_MAX ; 
 int /*<<< orphan*/  IPI_IRQ ; 
 int /*<<< orphan*/  TIMER_IRQ ; 
 int /*<<< orphan*/  cpu_interrupt_type ; 
 int /*<<< orphan*/  handle_percpu_irq ; 
 int /*<<< orphan*/  ipi_action ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_action ; 

__attribute__((used)) static void claim_cpu_irqs(void)
{
	int i;
	for (i = CPU_IRQ_BASE; i <= CPU_IRQ_MAX; i++) {
		irq_set_chip_and_handler(i, &cpu_interrupt_type,
					 handle_percpu_irq);
	}

	irq_set_handler(TIMER_IRQ, handle_percpu_irq);
	setup_irq(TIMER_IRQ, &timer_action);
#ifdef CONFIG_SMP
	irq_set_handler(IPI_IRQ, handle_percpu_irq);
	setup_irq(IPI_IRQ, &ipi_action);
#endif
}