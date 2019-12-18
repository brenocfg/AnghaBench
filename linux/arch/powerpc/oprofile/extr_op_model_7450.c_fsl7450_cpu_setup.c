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
struct op_counter_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_MMCR1 ; 
 int /*<<< orphan*/  SPRN_MMCR2 ; 
 int /*<<< orphan*/  mmcr0_val ; 
 int /*<<< orphan*/  mmcr1_val ; 
 int /*<<< orphan*/  mmcr2_val ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_pmcs ; 
 int /*<<< orphan*/  pmc_stop_ctrs () ; 

__attribute__((used)) static int fsl7450_cpu_setup(struct op_counter_config *ctr)
{
	/* freeze all counters */
	pmc_stop_ctrs();

	mtspr(SPRN_MMCR0, mmcr0_val);
	mtspr(SPRN_MMCR1, mmcr1_val);
	if (num_pmcs > 4)
		mtspr(SPRN_MMCR2, mmcr2_val);

	return 0;
}