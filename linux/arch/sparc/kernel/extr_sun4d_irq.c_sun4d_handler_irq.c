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
struct pt_regs {int dummy; } ;
struct irq_bucket {int /*<<< orphan*/  irq; struct irq_bucket* next; } ;

/* Variables and functions */
 unsigned int SUN4D_IPI_IRQ ; 
 int /*<<< orphan*/  cc_get_ipen () ; 
 int /*<<< orphan*/  cc_set_iclr (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 struct irq_bucket** irq_map ; 
 int* pil_to_sbus ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  sun4d_ipi_interrupt () ; 
 int /*<<< orphan*/  sun4d_sbus_handler_irq (int) ; 

void sun4d_handler_irq(unsigned int pil, struct pt_regs *regs)
{
	struct pt_regs *old_regs;
	/* SBUS IRQ level (1 - 7) */
	int sbusl = pil_to_sbus[pil];

	/* FIXME: Is this necessary?? */
	cc_get_ipen();

	cc_set_iclr(1 << pil);

#ifdef CONFIG_SMP
	/*
	 * Check IPI data structures after IRQ has been cleared. Hard and Soft
	 * IRQ can happen at the same time, so both cases are always handled.
	 */
	if (pil == SUN4D_IPI_IRQ)
		sun4d_ipi_interrupt();
#endif

	old_regs = set_irq_regs(regs);
	irq_enter();
	if (sbusl == 0) {
		/* cpu interrupt */
		struct irq_bucket *p;

		p = irq_map[pil];
		while (p) {
			struct irq_bucket *next;

			next = p->next;
			generic_handle_irq(p->irq);
			p = next;
		}
	} else {
		/* SBUS interrupt */
		sun4d_sbus_handler_irq(sbusl);
	}
	irq_exit();
	set_irq_regs(old_regs);
}