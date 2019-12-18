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
struct x86_perf_task_context {int dummy; } ;
struct perf_event_context {struct x86_perf_task_context* task_ctx_data; } ;
struct cpu_hw_events {int /*<<< orphan*/  lbr_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_pmu_lbr_restore (struct x86_perf_task_context*) ; 
 int /*<<< orphan*/  __intel_pmu_lbr_save (struct x86_perf_task_context*) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_lbr_reset () ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void intel_pmu_lbr_sched_task(struct perf_event_context *ctx, bool sched_in)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct x86_perf_task_context *task_ctx;

	if (!cpuc->lbr_users)
		return;

	/*
	 * If LBR callstack feature is enabled and the stack was saved when
	 * the task was scheduled out, restore the stack. Otherwise flush
	 * the LBR stack.
	 */
	task_ctx = ctx ? ctx->task_ctx_data : NULL;
	if (task_ctx) {
		if (sched_in)
			__intel_pmu_lbr_restore(task_ctx);
		else
			__intel_pmu_lbr_save(task_ctx);
		return;
	}

	/*
	 * Since a context switch can flip the address space and LBR entries
	 * are not tagged with an identifier, we need to wipe the LBR, even for
	 * per-cpu events. You simply cannot resolve the branches from the old
	 * address space.
	 */
	if (sched_in)
		intel_pmu_lbr_reset();
}