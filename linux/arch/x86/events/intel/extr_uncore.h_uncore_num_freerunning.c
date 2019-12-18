#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_1__ hw; } ;
struct intel_uncore_box {TYPE_4__* pmu; } ;
struct TYPE_8__ {TYPE_3__* type; } ;
struct TYPE_7__ {TYPE_2__* freerunning; } ;
struct TYPE_6__ {int num_counters; } ;

/* Variables and functions */
 unsigned int uncore_freerunning_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int uncore_num_freerunning(struct intel_uncore_box *box,
					 struct perf_event *event)
{
	unsigned int type = uncore_freerunning_type(event->hw.config);

	return box->pmu->type->freerunning[type].num_counters;
}