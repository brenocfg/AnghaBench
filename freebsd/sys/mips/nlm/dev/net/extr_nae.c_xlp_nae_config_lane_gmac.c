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

/* Variables and functions */
 int /*<<< orphan*/  LANE_CFG ; 
 int /*<<< orphan*/  LANE_CFG_CPLX_0_1 ; 
 int /*<<< orphan*/  LANE_CFG_CPLX_2_3 ; 
 int /*<<< orphan*/  LANE_CFG_CPLX_4 ; 
 int LM_SGMII ; 
 int /*<<< orphan*/  NAE_REG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYMODE_SGMII ; 
 int PHY_LANE_0_CTRL ; 
 int PHY_LANE_1_CTRL ; 
 int PHY_LANE_3_CTRL ; 
 int /*<<< orphan*/  nlm_is_xlp8xx_ax () ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xlp_ax_nae_lane_reset_txpll (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_nae_lane_reset_txpll (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
xlp_nae_config_lane_gmac(uint64_t nae_base, int cplx_mask)
{
	int block, lane_ctrl;
	int cplx_lane_enable;
	int lane_enable = 0;

	cplx_lane_enable = LM_SGMII |
	    (LM_SGMII << 4) |
	    (LM_SGMII << 8) |
	    (LM_SGMII << 12);

	/*  Lane mode progamming */
	block = 7;

	/* Complexes 0, 1 */
	if (cplx_mask & 0x1)
		lane_enable |= cplx_lane_enable;

	if (cplx_mask & 0x2)
		lane_enable |= (cplx_lane_enable << 16);

	if (lane_enable) {
		nlm_write_nae_reg(nae_base,
		    NAE_REG(block, LANE_CFG, LANE_CFG_CPLX_0_1),
		    lane_enable);
		lane_enable = 0;
	}
	/* Complexes 2 3 */
	if (cplx_mask & 0x4)
		lane_enable |= cplx_lane_enable;

	if (cplx_mask & 0x8)
		lane_enable |= (cplx_lane_enable << 16);

	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, LANE_CFG, LANE_CFG_CPLX_2_3),
	    lane_enable);

	/* complex 4 */
	/* XXXJC : fix duplicate code */
	if (cplx_mask & 0x10) {
		nlm_write_nae_reg(nae_base,
		    NAE_REG(block, LANE_CFG, LANE_CFG_CPLX_4),
		    ((LM_SGMII << 4) | LM_SGMII));
		for (lane_ctrl = PHY_LANE_0_CTRL;
		    lane_ctrl <= PHY_LANE_1_CTRL; lane_ctrl++) {
			if (!nlm_is_xlp8xx_ax())
				xlp_nae_lane_reset_txpll(nae_base,
				    4, lane_ctrl, PHYMODE_SGMII);
			else
				xlp_ax_nae_lane_reset_txpll(nae_base, 4,
				    lane_ctrl, PHYMODE_SGMII);
		}
	}

	for (block = 0; block < 4; block++) {
		if ((cplx_mask & (1 << block)) == 0)
			continue;

		for (lane_ctrl = PHY_LANE_0_CTRL;
		    lane_ctrl <= PHY_LANE_3_CTRL; lane_ctrl++) {
			if (!nlm_is_xlp8xx_ax())
				xlp_nae_lane_reset_txpll(nae_base,
				    block, lane_ctrl, PHYMODE_SGMII);
			else
				xlp_ax_nae_lane_reset_txpll(nae_base, block,
				    lane_ctrl, PHYMODE_SGMII);
		}
	}
}