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
struct pt_regs {int msr; int /*<<< orphan*/  link; int /*<<< orphan*/  nip; } ;

/* Variables and functions */
 int MSR_RI ; 
#define  SRR1_WAKEDEC 129 
#define  SRR1_WAKEEE 128 
 int SRR1_WAKEMASK ; 
 int /*<<< orphan*/  hard_smp_processor_id () ; 
 int /*<<< orphan*/  restore_astate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dec (int) ; 

__attribute__((used)) static int pasemi_system_reset_exception(struct pt_regs *regs)
{
	/* If we were woken up from power savings, we need to return
	 * to the calling function, since nip is not saved across
	 * all modes.
	 */

	if (regs->msr & SRR1_WAKEMASK)
		regs->nip = regs->link;

	switch (regs->msr & SRR1_WAKEMASK) {
	case SRR1_WAKEDEC:
		set_dec(1);
	case SRR1_WAKEEE:
		/*
		 * Handle these when interrupts get re-enabled and we take
		 * them as regular exceptions. We are in an NMI context
		 * and can't handle these here.
		 */
		break;
	default:
		/* do system reset */
		return 0;
	}

	/* Set higher astate since we come out of power savings at 0 */
	restore_astate(hard_smp_processor_id());

	/* everything handled */
	regs->msr |= MSR_RI;
	return 1;
}