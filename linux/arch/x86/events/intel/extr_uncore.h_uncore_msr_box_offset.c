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
struct intel_uncore_pmu {size_t pmu_idx; TYPE_1__* type; } ;
struct intel_uncore_box {struct intel_uncore_pmu* pmu; } ;
struct TYPE_2__ {int* msr_offsets; int msr_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned uncore_msr_box_offset(struct intel_uncore_box *box)
{
	struct intel_uncore_pmu *pmu = box->pmu;
	return pmu->type->msr_offsets ?
		pmu->type->msr_offsets[pmu->pmu_idx] :
		pmu->type->msr_offset * pmu->pmu_idx;
}