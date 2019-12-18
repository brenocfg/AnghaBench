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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LANE_CFG ; 
 int LANE_CFG_CPLX_0_1 ; 
 int LANE_CFG_CPLX_2_3 ; 
 int LANE_RX_CLK ; 
 int LANE_TX_CLK ; 
 int LM_XAUI ; 
 int NAE_REG (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY ; 
 int /*<<< orphan*/  PHYMODE_XAUI ; 
 int PHY_LANE_0_CTRL ; 
 int PHY_LANE_3_CTRL ; 
 int XAUI_LANE_FAULT ; 
 int /*<<< orphan*/  nlm_is_xlp8xx_ax () ; 
 void* nlm_read_nae_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xlp_ax_nae_lane_reset_txpll (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_nae_lane_reset_txpll (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
nlm_xaui_pcs_init(uint64_t nae_base, int xaui_cplx_mask)
{
	int block, lane_ctrl, reg;
	int cplx_lane_enable;
	int lane_enable = 0;
	uint32_t regval;

	cplx_lane_enable = LM_XAUI |
	    (LM_XAUI << 4) |
	    (LM_XAUI << 8) |
	    (LM_XAUI << 12);

	if (xaui_cplx_mask == 0)
		return;

	/* write 0x2 to enable SGMII for all lane */
	block = 7;

	if (xaui_cplx_mask & 0x3) { /* Complexes 0, 1 */
		lane_enable = nlm_read_nae_reg(nae_base,
		    NAE_REG(block, LANE_CFG, LANE_CFG_CPLX_0_1));
		if (xaui_cplx_mask & 0x1) { /* Complex 0 */
			lane_enable &= ~(0xFFFF);
			lane_enable |= cplx_lane_enable;
		}
		if (xaui_cplx_mask & 0x2) { /* Complex 1 */
			lane_enable &= ~(0xFFFF<<16);
			lane_enable |= (cplx_lane_enable << 16);
		}
		nlm_write_nae_reg(nae_base,
		    NAE_REG(block, LANE_CFG, LANE_CFG_CPLX_0_1),
		    lane_enable);
	}
	lane_enable = 0;
	if (xaui_cplx_mask & 0xc) { /* Complexes 2, 3 */
		lane_enable = nlm_read_nae_reg(nae_base,
		    NAE_REG(block, LANE_CFG, LANE_CFG_CPLX_2_3));
		if (xaui_cplx_mask & 0x4) { /* Complex 2 */
			lane_enable &= ~(0xFFFF);
			lane_enable |= cplx_lane_enable;
		}
		if (xaui_cplx_mask & 0x8) { /* Complex 3 */
			lane_enable &= ~(0xFFFF<<16);
			lane_enable |= (cplx_lane_enable << 16);
		}
		nlm_write_nae_reg(nae_base,
		    NAE_REG(block, LANE_CFG, LANE_CFG_CPLX_2_3),
		    lane_enable);
	}

	/* Bring txpll out of reset */
	for (block = 0; block < 4; block++) {
		if ((xaui_cplx_mask & (1 << block)) == 0)
			continue;

		for (lane_ctrl = PHY_LANE_0_CTRL;
		    lane_ctrl <= PHY_LANE_3_CTRL; lane_ctrl++) {
			if (!nlm_is_xlp8xx_ax())
				xlp_nae_lane_reset_txpll(nae_base,
				    block, lane_ctrl, PHYMODE_XAUI);
			else
				xlp_ax_nae_lane_reset_txpll(nae_base, block,
				    lane_ctrl, PHYMODE_XAUI);
		}
	}

	/* Wait for Rx & TX clock stable */
	for (block = 0; block < 4; block++) {
		if ((xaui_cplx_mask & (1 << block)) == 0)
			continue;

		for (lane_ctrl = PHY_LANE_0_CTRL;
		    lane_ctrl <= PHY_LANE_3_CTRL; lane_ctrl++) {

			reg = NAE_REG(block, PHY, lane_ctrl - 4);
			/* Wait for TX clock to be set */
			do {
				regval = nlm_read_nae_reg(nae_base, reg);
			} while ((regval & LANE_TX_CLK) == 0);

			/* Wait for RX clock to be set */
			do {
				regval = nlm_read_nae_reg(nae_base, reg);
			} while ((regval & LANE_RX_CLK) == 0);

			/* Wait for XAUI Lane fault to be cleared */
			do {
				regval = nlm_read_nae_reg(nae_base, reg);
			} while ((regval & XAUI_LANE_FAULT) != 0);
		}
	}
}