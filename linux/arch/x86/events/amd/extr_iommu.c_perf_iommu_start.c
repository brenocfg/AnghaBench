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
typedef  int /*<<< orphan*/  u64 ;
struct hw_perf_event {int state; int /*<<< orphan*/  iommu_cntr; int /*<<< orphan*/  iommu_bank; int /*<<< orphan*/  prev_count; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_PC_COUNTER_REG ; 
 int PERF_EF_RELOAD ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  amd_iommu_pc_set_reg (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_read (int /*<<< orphan*/ *) ; 
 struct amd_iommu* perf_event_2_iommu (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  perf_iommu_enable_event (struct perf_event*) ; 

__attribute__((used)) static void perf_iommu_start(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;

	if (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		return;

	WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));
	hwc->state = 0;

	if (flags & PERF_EF_RELOAD) {
		u64 prev_raw_count = local64_read(&hwc->prev_count);
		struct amd_iommu *iommu = perf_event_2_iommu(event);

		amd_iommu_pc_set_reg(iommu, hwc->iommu_bank, hwc->iommu_cntr,
				     IOMMU_PC_COUNTER_REG, &prev_raw_count);
	}

	perf_iommu_enable_event(event);
	perf_event_update_userpage(event);

}