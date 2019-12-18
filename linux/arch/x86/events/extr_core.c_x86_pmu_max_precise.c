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
struct TYPE_3__ {int pebs_format; } ;
struct TYPE_4__ {scalar_t__ pebs_prec_dist; TYPE_1__ intel_cap; scalar_t__ lbr_nr; int /*<<< orphan*/  pebs_broken; scalar_t__ pebs_active; } ;

/* Variables and functions */
 TYPE_2__ x86_pmu ; 

int x86_pmu_max_precise(void)
{
	int precise = 0;

	/* Support for constant skid */
	if (x86_pmu.pebs_active && !x86_pmu.pebs_broken) {
		precise++;

		/* Support for IP fixup */
		if (x86_pmu.lbr_nr || x86_pmu.intel_cap.pebs_format >= 2)
			precise++;

		if (x86_pmu.pebs_prec_dist)
			precise++;
	}
	return precise;
}