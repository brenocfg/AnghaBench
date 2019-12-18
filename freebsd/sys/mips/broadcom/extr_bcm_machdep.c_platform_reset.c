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
struct TYPE_2__ {scalar_t__ chip_id; } ;
struct bcm_platform {int pmu_addr; TYPE_1__ cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_CHIPC_WRITE_4 (struct bcm_platform*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BCM_PMU_WRITE_4 (struct bcm_platform*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ BHND_CHIPID_BCM4785 ; 
 int /*<<< orphan*/  BHND_PMU_WATCHDOG ; 
 int /*<<< orphan*/  BMIPS_BCMCFG_PLLCFG3_SM ; 
 int /*<<< orphan*/  CHIPC_WATCHDOG ; 
 int /*<<< orphan*/  bcm_bmips_wr_pllcfg3 (int /*<<< orphan*/ ) ; 
 struct bcm_platform* bcm_get_platform () ; 
 int /*<<< orphan*/  bcm_platform_data_avail ; 
 int /*<<< orphan*/  cfe_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  mips_sync () ; 
 int /*<<< orphan*/  printf (char*) ; 

void
platform_reset(void)
{
	struct bcm_platform	*bp;
	bool			 bcm4785war;

	printf("bcm::platform_reset()\n");
	intr_disable();

#ifdef CFE
	/* Fall back on CFE if reset requested during platform
	 * data initialization */
	if (!bcm_platform_data_avail) {
		cfe_exit(0, 0);
		while (1);
	}
#endif

	bp = bcm_get_platform();
	bcm4785war = false;

	/* Handle BCM4785-specific behavior */
	if (bp->cid.chip_id == BHND_CHIPID_BCM4785) {
		bcm4785war = true;

		/* Switch to async mode */
		bcm_bmips_wr_pllcfg3(BMIPS_BCMCFG_PLLCFG3_SM);
	}

	/* Set watchdog (PMU or ChipCommon) */
	if (bp->pmu_addr != 0x0) {
		BCM_PMU_WRITE_4(bp, BHND_PMU_WATCHDOG, 1);
	} else
		BCM_CHIPC_WRITE_4(bp, CHIPC_WATCHDOG, 1);

	/* BCM4785 */
	if (bcm4785war) {
		mips_sync();
		__asm __volatile("wait");
	}

	while (1);
}