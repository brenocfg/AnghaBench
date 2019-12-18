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
struct pt_regs {int dummy; } ;
struct perf_callchain_entry_ctx {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* is_in_guest ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fill_callchain ; 
 TYPE_1__* perf_guest_cbs ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  walk_stackframe (int /*<<< orphan*/ *,struct pt_regs*,int /*<<< orphan*/ ,struct perf_callchain_entry_ctx*) ; 

void perf_callchain_kernel(struct perf_callchain_entry_ctx *entry,
			   struct pt_regs *regs)
{
	/* RISC-V does not support perf in guest mode. */
	if (perf_guest_cbs && perf_guest_cbs->is_in_guest()) {
		pr_warn("RISC-V does not support perf in guest mode!");
		return;
	}

	walk_stackframe(NULL, regs, fill_callchain, entry);
}