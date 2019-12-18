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
struct stackframe {int /*<<< orphan*/  sp; int /*<<< orphan*/  lp; int /*<<< orphan*/  fp; } ;
struct pt_regs {int /*<<< orphan*/  sp; int /*<<< orphan*/  lp; int /*<<< orphan*/  fp; } ;
struct perf_callchain_entry_ctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* is_in_guest ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  callchain_trace ; 
 TYPE_1__* perf_guest_cbs ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  walk_stackframe (struct stackframe*,int /*<<< orphan*/ ,struct perf_callchain_entry_ctx*) ; 

void
perf_callchain_kernel(struct perf_callchain_entry_ctx *entry,
		      struct pt_regs *regs)
{
	struct stackframe fr;

	if (perf_guest_cbs && perf_guest_cbs->is_in_guest()) {
		/* We don't support guest os callchain now */
		return;
	}
	fr.fp = regs->fp;
	fr.lp = regs->lp;
	fr.sp = regs->sp;
	walk_stackframe(&fr, callchain_trace, entry);
}