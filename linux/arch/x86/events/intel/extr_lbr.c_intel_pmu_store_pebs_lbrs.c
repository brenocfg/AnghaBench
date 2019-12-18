#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct perf_branch_entry {int mispred; int predicted; int in_tx; int abort; int cycles; scalar_t__ reserved; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
struct pebs_lbr {TYPE_2__* lbr; } ;
struct TYPE_4__ {int nr; } ;
struct cpu_hw_events {struct perf_branch_entry* lbr_entries; TYPE_1__ lbr_stack; } ;
struct TYPE_6__ {int lbr_nr; } ;
struct TYPE_5__ {int info; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;

/* Variables and functions */
 int LBR_INFO_ABORT ; 
 int LBR_INFO_CYCLES ; 
 int LBR_INFO_IN_TX ; 
 int LBR_INFO_MISPRED ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_lbr_filter (struct cpu_hw_events*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_3__ x86_pmu ; 

void intel_pmu_store_pebs_lbrs(struct pebs_lbr *lbr)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int i;

	cpuc->lbr_stack.nr = x86_pmu.lbr_nr;
	for (i = 0; i < x86_pmu.lbr_nr; i++) {
		u64 info = lbr->lbr[i].info;
		struct perf_branch_entry *e = &cpuc->lbr_entries[i];

		e->from		= lbr->lbr[i].from;
		e->to		= lbr->lbr[i].to;
		e->mispred	= !!(info & LBR_INFO_MISPRED);
		e->predicted	= !(info & LBR_INFO_MISPRED);
		e->in_tx	= !!(info & LBR_INFO_IN_TX);
		e->abort	= !!(info & LBR_INFO_ABORT);
		e->cycles	= info & LBR_INFO_CYCLES;
		e->reserved	= 0;
	}
	intel_pmu_lbr_filter(cpuc);
}