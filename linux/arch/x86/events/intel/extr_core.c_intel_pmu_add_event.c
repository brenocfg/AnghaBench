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
struct TYPE_2__ {scalar_t__ precise_ip; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pmu_lbr_add (struct perf_event*) ; 
 int /*<<< orphan*/  intel_pmu_pebs_add (struct perf_event*) ; 
 scalar_t__ needs_branch_stack (struct perf_event*) ; 

__attribute__((used)) static void intel_pmu_add_event(struct perf_event *event)
{
	if (event->attr.precise_ip)
		intel_pmu_pebs_add(event);
	if (needs_branch_stack(event))
		intel_pmu_lbr_add(event);
}