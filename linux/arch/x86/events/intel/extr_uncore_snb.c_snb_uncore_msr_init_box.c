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
struct intel_uncore_box {TYPE_1__* pmu; } ;
struct TYPE_2__ {scalar_t__ pmu_idx; } ;

/* Variables and functions */
 int SNB_UNC_GLOBAL_CTL_CORE_ALL ; 
 int SNB_UNC_GLOBAL_CTL_EN ; 
 int /*<<< orphan*/  SNB_UNC_PERF_GLOBAL_CTL ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snb_uncore_msr_init_box(struct intel_uncore_box *box)
{
	if (box->pmu->pmu_idx == 0) {
		wrmsrl(SNB_UNC_PERF_GLOBAL_CTL,
			SNB_UNC_GLOBAL_CTL_EN | SNB_UNC_GLOBAL_CTL_CORE_ALL);
	}
}