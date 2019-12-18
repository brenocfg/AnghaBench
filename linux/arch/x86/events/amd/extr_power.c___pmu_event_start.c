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
struct TYPE_2__ {int state; int /*<<< orphan*/  pwr_acc; int /*<<< orphan*/  ptsc; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_F15H_CU_PWR_ACCUMULATOR ; 
 int /*<<< orphan*/  MSR_F15H_PTSC ; 
 int PERF_HES_STOPPED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pmu_event_start(struct perf_event *event)
{
	if (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		return;

	event->hw.state = 0;

	rdmsrl(MSR_F15H_PTSC, event->hw.ptsc);
	rdmsrl(MSR_F15H_CU_PWR_ACCUMULATOR, event->hw.pwr_acc);
}