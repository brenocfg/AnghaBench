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
typedef  int u64 ;
struct hw_perf_event {int /*<<< orphan*/  prev_count; int /*<<< orphan*/  iommu_cntr; int /*<<< orphan*/  iommu_bank; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int COUNTER_SHIFT ; 
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMMU_PC_COUNTER_REG ; 
 scalar_t__ amd_iommu_pc_get_reg (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  local64_add (int,int /*<<< orphan*/ *) ; 
 int local64_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 struct amd_iommu* perf_event_2_iommu (struct perf_event*) ; 

__attribute__((used)) static void perf_iommu_read(struct perf_event *event)
{
	u64 count, prev, delta;
	struct hw_perf_event *hwc = &event->hw;
	struct amd_iommu *iommu = perf_event_2_iommu(event);

	if (amd_iommu_pc_get_reg(iommu, hwc->iommu_bank, hwc->iommu_cntr,
				 IOMMU_PC_COUNTER_REG, &count))
		return;

	/* IOMMU pc counter register is only 48 bits */
	count &= GENMASK_ULL(47, 0);

	prev = local64_read(&hwc->prev_count);
	if (local64_cmpxchg(&hwc->prev_count, prev, count) != prev)
		return;

	/* Handle 48-bit counter overflow */
	delta = (count << COUNTER_SHIFT) - (prev << COUNTER_SHIFT);
	delta >>= COUNTER_SHIFT;
	local64_add(delta, &event->count);
}