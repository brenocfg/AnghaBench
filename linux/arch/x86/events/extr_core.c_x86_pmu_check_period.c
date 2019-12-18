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
typedef  scalar_t__ u64 ;
struct perf_event {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* limit_period ) (struct perf_event*,scalar_t__) ;scalar_t__ (* check_period ) (struct perf_event*,scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ stub1 (struct perf_event*,scalar_t__) ; 
 scalar_t__ stub2 (struct perf_event*,scalar_t__) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int x86_pmu_check_period(struct perf_event *event, u64 value)
{
	if (x86_pmu.check_period && x86_pmu.check_period(event, value))
		return -EINVAL;

	if (value && x86_pmu.limit_period) {
		if (x86_pmu.limit_period(event, value) > value)
			return -EINVAL;
	}

	return 0;
}