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
struct task_struct {int dummy; } ;
struct TYPE_2__ {struct task_struct* target; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ is_compat_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 

__attribute__((used)) static int is_compat_bp(struct perf_event *bp)
{
	struct task_struct *tsk = bp->hw.target;

	/*
	 * tsk can be NULL for per-cpu (non-ptrace) breakpoints.
	 * In this case, use the native interface, since we don't have
	 * the notion of a "compat CPU" and could end up relying on
	 * deprecated behaviour if we use unaligned watchpoints in
	 * AArch64 state.
	 */
	return tsk && is_compat_thread(task_thread_info(tsk));
}