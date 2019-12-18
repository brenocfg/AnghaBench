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
struct hw_perf_event {int idx; int state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  HPCNTENR ; 
 int /*<<< orphan*/  HPINTENR ; 
 int PERF_EF_RELOAD ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int cprcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpwcr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csky_pmu_event_set_period (struct perf_event*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void csky_pmu_start(struct perf_event *event, int flags)
{
	unsigned long flg;
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (WARN_ON_ONCE(idx == -1))
		return;

	if (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	csky_pmu_event_set_period(event);

	local_irq_save(flg);

	cpwcr(HPINTENR, BIT(idx) | cprcr(HPINTENR));
	cpwcr(HPCNTENR, BIT(idx) | cprcr(HPCNTENR));

	local_irq_restore(flg);
}