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
struct x86_pmu_capability {unsigned int events_mask; int /*<<< orphan*/  events_mask_len; int /*<<< orphan*/  bit_width_fixed; int /*<<< orphan*/  bit_width_gp; int /*<<< orphan*/  num_counters_fixed; int /*<<< orphan*/  num_counters_gp; int /*<<< orphan*/  version; } ;
struct TYPE_2__ {int /*<<< orphan*/  events_mask_len; scalar_t__ events_maskl; int /*<<< orphan*/  cntval_bits; int /*<<< orphan*/  num_counters_fixed; int /*<<< orphan*/  num_counters; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 TYPE_1__ x86_pmu ; 

void perf_get_x86_pmu_capability(struct x86_pmu_capability *cap)
{
	cap->version		= x86_pmu.version;
	cap->num_counters_gp	= x86_pmu.num_counters;
	cap->num_counters_fixed	= x86_pmu.num_counters_fixed;
	cap->bit_width_gp	= x86_pmu.cntval_bits;
	cap->bit_width_fixed	= x86_pmu.cntval_bits;
	cap->events_mask	= (unsigned int)x86_pmu.events_maskl;
	cap->events_mask_len	= x86_pmu.events_mask_len;
}