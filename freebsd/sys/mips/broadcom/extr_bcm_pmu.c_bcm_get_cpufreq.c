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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct bcm_platform {int /*<<< orphan*/  cid; int /*<<< orphan*/  cc_caps; } ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_CHIPC_READ_4 (struct bcm_platform*,scalar_t__) ; 
 int /*<<< orphan*/  CHIPC_CAP_PLL ; 
 scalar_t__ CHIPC_CLKC_N ; 
 int /*<<< orphan*/  CHIPC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_get_pmu (struct bcm_platform*) ; 
 scalar_t__ bcm_has_pmu (struct bcm_platform*) ; 
 int /*<<< orphan*/  bhnd_pmu_cpu_clock (int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_pwrctl_cpu_clkreg_m (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_pwrctl_cpu_clock_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
bcm_get_cpufreq(struct bcm_platform *bp)
{
	uint32_t		 fixed_hz;
	uint32_t		 n, m;
	bus_size_t		 mreg;
	uint8_t			 pll_type;

	/* PMU support */
	if (bcm_has_pmu(bp))
		return (bhnd_pmu_cpu_clock(bcm_get_pmu(bp)));

	/*
	 * PWRCTL support
	 */
	pll_type = CHIPC_GET_BITS(bp->cc_caps, CHIPC_CAP_PLL);
	mreg = bhnd_pwrctl_cpu_clkreg_m(&bp->cid, pll_type, &fixed_hz);
	if (mreg == 0)
		return (fixed_hz);

	n = BCM_CHIPC_READ_4(bp, CHIPC_CLKC_N);
	m = BCM_CHIPC_READ_4(bp, mreg);

	return (bhnd_pwrctl_cpu_clock_rate(&bp->cid, pll_type, n, m));
	
}