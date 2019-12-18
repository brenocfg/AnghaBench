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
typedef  int /*<<< orphan*/  uint64_t ;
struct bcm_platform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU_ILP_CLOCK ; 
 int /*<<< orphan*/  bcm_get_pmu (struct bcm_platform*) ; 
 int /*<<< orphan*/  bcm_has_pmu (struct bcm_platform*) ; 
 int /*<<< orphan*/  bhnd_pmu_ilp_clock (int /*<<< orphan*/ ) ; 

uint64_t
bcm_get_ilpfreq(struct bcm_platform *bp) {
	if (!bcm_has_pmu(bp))
		return (BHND_PMU_ILP_CLOCK);

	return (bhnd_pmu_ilp_clock(bcm_get_pmu(bp)));
}