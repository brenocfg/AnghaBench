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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ intel_pmu_has_bts_period (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pmu_check_period(struct perf_event *event, u64 value)
{
	return intel_pmu_has_bts_period(event, value) ? -EINVAL : 0;
}