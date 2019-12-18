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
struct hw_perf_event {int idx; int state; int config; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_PCT_CONFIG ; 
 int /*<<< orphan*/  ARC_REG_PCT_INDEX ; 
 int /*<<< orphan*/  ARC_REG_PCT_INT_CTRL ; 
 int BIT (int) ; 
 int PERF_EF_RELOAD ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  arc_pmu_event_set_period (struct perf_event*) ; 
 scalar_t__ is_sampling_event (struct perf_event*) ; 
 int read_aux_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arc_pmu_start(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (WARN_ON_ONCE(idx == -1))
		return;

	if (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	arc_pmu_event_set_period(event);

	/* Enable interrupt for this counter */
	if (is_sampling_event(event))
		write_aux_reg(ARC_REG_PCT_INT_CTRL,
			      read_aux_reg(ARC_REG_PCT_INT_CTRL) | BIT(idx));

	/* enable ARC pmu here */
	write_aux_reg(ARC_REG_PCT_INDEX, idx);		/* counter # */
	write_aux_reg(ARC_REG_PCT_CONFIG, hwc->config);	/* condition */
}