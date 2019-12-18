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
struct intel_uncore_box {TYPE_2__* pmu; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int num_freerunning_types; } ;

/* Variables and functions */

__attribute__((used)) static inline int uncore_num_freerunning_types(struct intel_uncore_box *box,
					       struct perf_event *event)
{
	return box->pmu->type->num_freerunning_types;
}