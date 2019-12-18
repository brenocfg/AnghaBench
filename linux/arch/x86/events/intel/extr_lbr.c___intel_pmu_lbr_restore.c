#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct x86_perf_task_context {scalar_t__ lbr_callstack_users; scalar_t__ lbr_stack_state; int tos; scalar_t__ log_id; int valid_lbrs; int* lbr_info; int /*<<< orphan*/ * lbr_to; int /*<<< orphan*/ * lbr_from; } ;
struct cpu_hw_events {scalar_t__ last_log_id; struct x86_perf_task_context* last_task_ctx; } ;
struct TYPE_3__ {scalar_t__ lbr_format; } ;
struct TYPE_4__ {int lbr_nr; scalar_t__ lbr_tos; TYPE_1__ intel_cap; } ;

/* Variables and functions */
 scalar_t__ LBR_FORMAT_INFO ; 
 scalar_t__ LBR_NONE ; 
 scalar_t__ MSR_LBR_INFO_0 ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_lbr_reset () ; 
 scalar_t__ rdlbr_from (int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrlbr_from (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrlbr_to (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (scalar_t__,int) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static void __intel_pmu_lbr_restore(struct x86_perf_task_context *task_ctx)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int i;
	unsigned lbr_idx, mask;
	u64 tos;

	if (task_ctx->lbr_callstack_users == 0 ||
	    task_ctx->lbr_stack_state == LBR_NONE) {
		intel_pmu_lbr_reset();
		return;
	}

	tos = task_ctx->tos;
	/*
	 * Does not restore the LBR registers, if
	 * - No one else touched them, and
	 * - Did not enter C6
	 */
	if ((task_ctx == cpuc->last_task_ctx) &&
	    (task_ctx->log_id == cpuc->last_log_id) &&
	    rdlbr_from(tos)) {
		task_ctx->lbr_stack_state = LBR_NONE;
		return;
	}

	mask = x86_pmu.lbr_nr - 1;
	for (i = 0; i < task_ctx->valid_lbrs; i++) {
		lbr_idx = (tos - i) & mask;
		wrlbr_from(lbr_idx, task_ctx->lbr_from[i]);
		wrlbr_to  (lbr_idx, task_ctx->lbr_to[i]);

		if (x86_pmu.intel_cap.lbr_format == LBR_FORMAT_INFO)
			wrmsrl(MSR_LBR_INFO_0 + lbr_idx, task_ctx->lbr_info[i]);
	}

	for (; i < x86_pmu.lbr_nr; i++) {
		lbr_idx = (tos - i) & mask;
		wrlbr_from(lbr_idx, 0);
		wrlbr_to(lbr_idx, 0);
		if (x86_pmu.intel_cap.lbr_format == LBR_FORMAT_INFO)
			wrmsrl(MSR_LBR_INFO_0 + lbr_idx, 0);
	}

	wrmsrl(x86_pmu.lbr_tos, tos);
	task_ctx->lbr_stack_state = LBR_NONE;
}