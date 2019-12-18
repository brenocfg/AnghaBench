#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct unwind_state {int dummy; } ;
struct pt_regs {unsigned long ip; scalar_t__ sp; } ;
struct perf_callchain_entry_ctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* is_in_guest ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 scalar_t__ perf_callchain_store (struct perf_callchain_entry_ctx*,unsigned long) ; 
 TYPE_1__* perf_guest_cbs ; 
 scalar_t__ perf_hw_regs (struct pt_regs*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  unwind_done (struct unwind_state*) ; 
 unsigned long unwind_get_return_address (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_next_frame (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_start (struct unwind_state*,int /*<<< orphan*/ ,struct pt_regs*,void*) ; 

void
perf_callchain_kernel(struct perf_callchain_entry_ctx *entry, struct pt_regs *regs)
{
	struct unwind_state state;
	unsigned long addr;

	if (perf_guest_cbs && perf_guest_cbs->is_in_guest()) {
		/* TODO: We don't support guest os callchain now */
		return;
	}

	if (perf_callchain_store(entry, regs->ip))
		return;

	if (perf_hw_regs(regs))
		unwind_start(&state, current, regs, NULL);
	else
		unwind_start(&state, current, NULL, (void *)regs->sp);

	for (; !unwind_done(&state); unwind_next_frame(&state)) {
		addr = unwind_get_return_address(&state);
		if (!addr || perf_callchain_store(entry, addr))
			return;
	}
}