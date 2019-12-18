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
struct perf_event {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pebs_output_pt_available; } ;
struct TYPE_4__ {TYPE_1__ intel_cap; } ;

/* Variables and functions */
 int is_intel_pt_event (struct perf_event*) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static int intel_pmu_aux_output_match(struct perf_event *event)
{
	if (!x86_pmu.intel_cap.pebs_output_pt_available)
		return 0;

	return is_intel_pt_event(event);
}