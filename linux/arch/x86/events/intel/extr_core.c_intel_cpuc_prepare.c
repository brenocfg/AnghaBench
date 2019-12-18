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
struct event_constraint {int dummy; } ;
struct cpu_hw_events {int /*<<< orphan*/ * shared_regs; int /*<<< orphan*/ * constraint_list; scalar_t__ excl_thread_id; int /*<<< orphan*/  excl_cntrs; int /*<<< orphan*/  pebs_record_size; } ;
struct TYPE_2__ {int flags; scalar_t__ lbr_sel_map; scalar_t__ extra_regs; int /*<<< orphan*/  pebs_record_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PMU_FL_EXCL_CNTRS ; 
 int PMU_FL_TFA ; 
 int X86_PMC_IDX_MAX ; 
 int /*<<< orphan*/  allocate_excl_cntrs (int) ; 
 int /*<<< orphan*/ * allocate_shared_regs (int) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc_node (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ x86_pmu ; 

int intel_cpuc_prepare(struct cpu_hw_events *cpuc, int cpu)
{
	cpuc->pebs_record_size = x86_pmu.pebs_record_size;

	if (x86_pmu.extra_regs || x86_pmu.lbr_sel_map) {
		cpuc->shared_regs = allocate_shared_regs(cpu);
		if (!cpuc->shared_regs)
			goto err;
	}

	if (x86_pmu.flags & (PMU_FL_EXCL_CNTRS | PMU_FL_TFA)) {
		size_t sz = X86_PMC_IDX_MAX * sizeof(struct event_constraint);

		cpuc->constraint_list = kzalloc_node(sz, GFP_KERNEL, cpu_to_node(cpu));
		if (!cpuc->constraint_list)
			goto err_shared_regs;
	}

	if (x86_pmu.flags & PMU_FL_EXCL_CNTRS) {
		cpuc->excl_cntrs = allocate_excl_cntrs(cpu);
		if (!cpuc->excl_cntrs)
			goto err_constraint_list;

		cpuc->excl_thread_id = 0;
	}

	return 0;

err_constraint_list:
	kfree(cpuc->constraint_list);
	cpuc->constraint_list = NULL;

err_shared_regs:
	kfree(cpuc->shared_regs);
	cpuc->shared_regs = NULL;

err:
	return -ENOMEM;
}