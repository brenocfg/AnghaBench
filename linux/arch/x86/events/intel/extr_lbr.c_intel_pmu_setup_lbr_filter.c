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
struct perf_event {int dummy; } ;
struct TYPE_2__ {scalar_t__ lbr_sel_map; int /*<<< orphan*/  lbr_nr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int intel_pmu_setup_hw_lbr_filter (struct perf_event*) ; 
 int intel_pmu_setup_sw_lbr_filter (struct perf_event*) ; 
 TYPE_1__ x86_pmu ; 

int intel_pmu_setup_lbr_filter(struct perf_event *event)
{
	int ret = 0;

	/*
	 * no LBR on this PMU
	 */
	if (!x86_pmu.lbr_nr)
		return -EOPNOTSUPP;

	/*
	 * setup SW LBR filter
	 */
	ret = intel_pmu_setup_sw_lbr_filter(event);
	if (ret)
		return ret;

	/*
	 * setup HW LBR filter, if any
	 */
	if (x86_pmu.lbr_sel_map)
		ret = intel_pmu_setup_hw_lbr_filter(event);

	return ret;
}