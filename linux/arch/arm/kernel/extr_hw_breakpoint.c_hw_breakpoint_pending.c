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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_DBG_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ARM_DSCR_MOE (int /*<<< orphan*/ ) ; 
#define  ARM_ENTRY_ASYNC_WATCHPOINT 130 
#define  ARM_ENTRY_BREAKPOINT 129 
#define  ARM_ENTRY_SYNC_WATCHPOINT 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  breakpoint_handler (unsigned long,struct pt_regs*) ; 
 int /*<<< orphan*/  c0 ; 
 int /*<<< orphan*/  c1 ; 
 scalar_t__ interrupts_enabled (struct pt_regs*) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  watchpoint_handler (unsigned long,unsigned int,struct pt_regs*) ; 

__attribute__((used)) static int hw_breakpoint_pending(unsigned long addr, unsigned int fsr,
				 struct pt_regs *regs)
{
	int ret = 0;
	u32 dscr;

	preempt_disable();

	if (interrupts_enabled(regs))
		local_irq_enable();

	/* We only handle watchpoints and hardware breakpoints. */
	ARM_DBG_READ(c0, c1, 0, dscr);

	/* Perform perf callbacks. */
	switch (ARM_DSCR_MOE(dscr)) {
	case ARM_ENTRY_BREAKPOINT:
		breakpoint_handler(addr, regs);
		break;
	case ARM_ENTRY_ASYNC_WATCHPOINT:
		WARN(1, "Asynchronous watchpoint exception taken. Debugging results may be unreliable\n");
		/* Fall through */
	case ARM_ENTRY_SYNC_WATCHPOINT:
		watchpoint_handler(addr, fsr, regs);
		break;
	default:
		ret = 1; /* Unhandled fault. */
	}

	preempt_enable();

	return ret;
}