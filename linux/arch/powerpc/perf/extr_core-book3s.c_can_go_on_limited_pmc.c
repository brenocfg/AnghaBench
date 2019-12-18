#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {scalar_t__ sample_period; scalar_t__ exclude_hv; scalar_t__ exclude_kernel; scalar_t__ exclude_user; } ;
struct perf_event {TYPE_1__ attr; } ;
struct TYPE_4__ {int (* get_alternatives ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ;scalar_t__ (* limited_pmc_event ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_EVENT_ALTERNATIVES ; 
 unsigned int PPMU_LIMITED_PMC_OK ; 
 unsigned int PPMU_LIMITED_PMC_REQD ; 
 TYPE_2__* ppmu ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int can_go_on_limited_pmc(struct perf_event *event, u64 ev,
				 unsigned int flags)
{
	int n;
	u64 alt[MAX_EVENT_ALTERNATIVES];

	if (event->attr.exclude_user
	    || event->attr.exclude_kernel
	    || event->attr.exclude_hv
	    || event->attr.sample_period)
		return 0;

	if (ppmu->limited_pmc_event(ev))
		return 1;

	/*
	 * The requested event_id isn't on a limited PMC already;
	 * see if any alternative code goes on a limited PMC.
	 */
	if (!ppmu->get_alternatives)
		return 0;

	flags |= PPMU_LIMITED_PMC_OK | PPMU_LIMITED_PMC_REQD;
	n = ppmu->get_alternatives(ev, flags, alt);

	return n > 0;
}