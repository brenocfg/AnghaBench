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
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_3__ hw; } ;
struct intel_uncore_pmu {int pmu_idx; TYPE_2__* type; } ;
struct intel_uncore_box {struct intel_uncore_pmu* pmu; } ;
struct TYPE_5__ {TYPE_1__* freerunning; } ;
struct TYPE_4__ {unsigned int counter_base; unsigned int counter_offset; int box_offset; } ;

/* Variables and functions */
 unsigned int uncore_freerunning_idx (int /*<<< orphan*/ ) ; 
 unsigned int uncore_freerunning_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
unsigned int uncore_freerunning_counter(struct intel_uncore_box *box,
					struct perf_event *event)
{
	unsigned int type = uncore_freerunning_type(event->hw.config);
	unsigned int idx = uncore_freerunning_idx(event->hw.config);
	struct intel_uncore_pmu *pmu = box->pmu;

	return pmu->type->freerunning[type].counter_base +
	       pmu->type->freerunning[type].counter_offset * idx +
	       pmu->type->freerunning[type].box_offset * pmu->pmu_idx;
}