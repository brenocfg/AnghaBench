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
struct TYPE_4__ {int capabilities; } ;
struct TYPE_3__ {int (* aux_output_match ) (struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_PMU_CAP_AUX_OUTPUT ; 
 TYPE_2__ pmu ; 
 int stub1 (struct perf_event*) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static int x86_pmu_aux_output_match(struct perf_event *event)
{
	if (!(pmu.capabilities & PERF_PMU_CAP_AUX_OUTPUT))
		return 0;

	if (x86_pmu.aux_output_match)
		return x86_pmu.aux_output_match(event);

	return 0;
}