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
struct hw_perf_event {scalar_t__ idx; int config; int /*<<< orphan*/  config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int SNB_UNC_CTL_EN ; 
 scalar_t__ UNCORE_PMC_IDX_FIXED ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snb_uncore_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	if (hwc->idx < UNCORE_PMC_IDX_FIXED)
		wrmsrl(hwc->config_base, hwc->config | SNB_UNC_CTL_EN);
	else
		wrmsrl(hwc->config_base, SNB_UNC_CTL_EN);
}