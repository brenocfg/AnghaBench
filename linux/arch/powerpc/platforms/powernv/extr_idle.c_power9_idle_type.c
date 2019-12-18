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
 int /*<<< orphan*/  SPRN_PSSCR ; 
 int /*<<< orphan*/  __ppc64_runlatch_off () ; 
 int /*<<< orphan*/  __ppc64_runlatch_on () ; 
 int /*<<< orphan*/  fini_irq_for_idle_irqsoff () ; 
 int /*<<< orphan*/  irq_set_pending_from_srr1 (unsigned long) ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 unsigned long power9_idle_stop (unsigned long,int) ; 
 int /*<<< orphan*/  prep_irq_for_idle_irqsoff () ; 

void power9_idle_type(unsigned long stop_psscr_val,
				      unsigned long stop_psscr_mask)
{
	unsigned long psscr;
	unsigned long srr1;

	if (!prep_irq_for_idle_irqsoff())
		return;

	psscr = mfspr(SPRN_PSSCR);
	psscr = (psscr & ~stop_psscr_mask) | stop_psscr_val;

	__ppc64_runlatch_off();
	srr1 = power9_idle_stop(psscr, true);
	__ppc64_runlatch_on();

	fini_irq_for_idle_irqsoff();

	irq_set_pending_from_srr1(srr1);
}