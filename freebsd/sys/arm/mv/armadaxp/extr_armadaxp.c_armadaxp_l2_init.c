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
typedef  int u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARMADAXP_L2_AUX_CTRL ; 
 int /*<<< orphan*/  ARMADAXP_L2_CNTR_CONF (int) ; 
 int /*<<< orphan*/  ARMADAXP_L2_CNTR_CTRL ; 
 int /*<<< orphan*/  ARMADAXP_L2_CTRL ; 
 int /*<<< orphan*/  ARMADAXP_L2_INT_CAUSE ; 
 int /*<<< orphan*/  COHER_FABRIC_CFU ; 
 int /*<<< orphan*/  COHER_FABRIC_CIB_CTRL ; 
 int L2_ENABLE ; 
 int L2_REP_STRAT_MASK ; 
 int L2_REP_STRAT_SEMIPLRU ; 
 int L2_WBWT_MODE_MASK ; 
 int L2_WBWT_MODE_WT ; 
 int /*<<< orphan*/  armadaxp_l2_idcache_inv_all () ; 
 int read_coher_fabric (int /*<<< orphan*/ ) ; 
 int read_l2_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_coher_fabric (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_l2_cache (int /*<<< orphan*/ ,int) ; 

void
armadaxp_l2_init(void)
{
	u_int32_t reg;

	/* Set L2 policy */
	reg = read_l2_cache(ARMADAXP_L2_AUX_CTRL);
	reg &= ~(L2_WBWT_MODE_MASK);
	reg &= ~(L2_REP_STRAT_MASK);
	reg |= L2_REP_STRAT_SEMIPLRU;
	reg |= L2_WBWT_MODE_WT;
	write_l2_cache(ARMADAXP_L2_AUX_CTRL, reg);

	/* Invalidate l2 cache */
	armadaxp_l2_idcache_inv_all();

	/* Clear pending L2 interrupts */
	write_l2_cache(ARMADAXP_L2_INT_CAUSE, 0x1ff);

	/* Enable l2 cache */
	reg = read_l2_cache(ARMADAXP_L2_CTRL);
	write_l2_cache(ARMADAXP_L2_CTRL, reg | L2_ENABLE);

	/*
	 * For debug purposes
	 * Configure and enable counter
	 */
	write_l2_cache(ARMADAXP_L2_CNTR_CONF(0), 0xf0000 | (4 << 2));
	write_l2_cache(ARMADAXP_L2_CNTR_CONF(1), 0xf0000 | (2 << 2));
	write_l2_cache(ARMADAXP_L2_CNTR_CTRL, 0x303);

	/*
	 * Enable Cache maintenance operation propagation in coherency fabric
	 * Change point of coherency and point of unification to DRAM.
	 */
	reg = read_coher_fabric(COHER_FABRIC_CFU);
	reg |= (1 << 17) | (1 << 18);
	write_coher_fabric(COHER_FABRIC_CFU, reg);

	/* Coherent IO Bridge initialization */
	reg = read_coher_fabric(COHER_FABRIC_CIB_CTRL);
	reg &= ~(7 << 16);
	reg |= (7 << 16);
	write_coher_fabric(COHER_FABRIC_CIB_CTRL, reg);
}