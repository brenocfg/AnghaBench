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
struct thread_struct {int debugreg6; struct perf_event** ptrace_bps; } ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_event {int dummy; } ;
struct TYPE_2__ {struct thread_struct thread; } ;

/* Variables and functions */
 int DR_TRAP0 ; 
 int HBP_NUM ; 
 TYPE_1__* current ; 

__attribute__((used)) static void ptrace_triggered(struct perf_event *bp,
			     struct perf_sample_data *data,
			     struct pt_regs *regs)
{
	int i;
	struct thread_struct *thread = &(current->thread);

	/*
	 * Store in the virtual DR6 register the fact that the breakpoint
	 * was hit so the thread's debugger will see it.
	 */
	for (i = 0; i < HBP_NUM; i++) {
		if (thread->ptrace_bps[i] == bp)
			break;
	}

	thread->debugreg6 |= (DR_TRAP0 << i);
}