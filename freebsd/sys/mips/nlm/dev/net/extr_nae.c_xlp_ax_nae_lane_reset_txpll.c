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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  NAE_REG (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY ; 
 int PHYMODE_SGMII ; 
 int PHY_LANE_0_CTRL ; 
 int PHY_LANE_CTRL_ADDR_POS ; 
 int PHY_LANE_CTRL_BPC_XAUI ; 
 int PHY_LANE_CTRL_CMD_PENDING ; 
 int PHY_LANE_CTRL_CMD_READ ; 
 int PHY_LANE_CTRL_CMD_START ; 
 int PHY_LANE_CTRL_CMD_WRITE ; 
 int PHY_LANE_CTRL_PHYMODE_POS ; 
 int PHY_LANE_CTRL_PWRDOWN ; 
 int PHY_LANE_CTRL_RST ; 
 int PHY_LANE_STAT_PCR ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
xlp_ax_nae_lane_reset_txpll(uint64_t nae_base, int block, int lane_ctrl,
    int mode)
{
	uint32_t val = 0, saved_data;
	int rext_sel = 0;

	val = PHY_LANE_CTRL_RST |
	    PHY_LANE_CTRL_PWRDOWN |
	    (mode << PHY_LANE_CTRL_PHYMODE_POS);

	/* set comma bypass for XAUI */
	if (mode != PHYMODE_SGMII)
		val |= PHY_LANE_CTRL_BPC_XAUI;

	nlm_write_nae_reg(nae_base, NAE_REG(block, PHY, lane_ctrl), val);

	if (lane_ctrl != 4) {
		rext_sel = (1 << 23);
		if (mode != PHYMODE_SGMII)
			rext_sel |= PHY_LANE_CTRL_BPC_XAUI;

		val = nlm_read_nae_reg(nae_base,
		    NAE_REG(block, PHY, lane_ctrl));
		val &= ~PHY_LANE_CTRL_RST;
		val |= rext_sel;

		/* Resetting PMA for non-zero lanes */
		nlm_write_nae_reg(nae_base,
		    NAE_REG(block, PHY, lane_ctrl), val);

		DELAY(20000);	/* 20 ms delay, XXXJC: needed? */

		val |= PHY_LANE_CTRL_RST;
		nlm_write_nae_reg(nae_base,
		    NAE_REG(block, PHY, lane_ctrl), val);

		val = 0;
	}

	/* Come out of reset for TXPLL */
	saved_data = nlm_read_nae_reg(nae_base,
	    NAE_REG(block, PHY, lane_ctrl)) & 0xFFC00000;

	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, PHY, lane_ctrl),
	    (0x66 << PHY_LANE_CTRL_ADDR_POS)
	    | PHY_LANE_CTRL_CMD_READ
	    | PHY_LANE_CTRL_CMD_START
	    | PHY_LANE_CTRL_RST
	    | rext_sel
	    | val );

	while (((val = nlm_read_nae_reg(nae_base,
	    NAE_REG(block, PHY, lane_ctrl))) &
	    PHY_LANE_CTRL_CMD_PENDING));

	val &= 0xFF;
	/* set bit[4] to 0 */
	val &= ~(1 << 4);
	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, PHY, lane_ctrl),
	    (0x66 << PHY_LANE_CTRL_ADDR_POS)
	    | PHY_LANE_CTRL_CMD_WRITE
	    | PHY_LANE_CTRL_CMD_START
	    | (0x0 << 19) /* (0x4 << 19) */
	    | rext_sel
	    | saved_data
	    | val );

	/* re-do */
	nlm_write_nae_reg(nae_base,
	    NAE_REG(block, PHY, lane_ctrl),
	    (0x66 << PHY_LANE_CTRL_ADDR_POS)
	    | PHY_LANE_CTRL_CMD_WRITE
	    | PHY_LANE_CTRL_CMD_START
	    | (0x0 << 19) /* (0x4 << 19) */
	    | rext_sel
	    | saved_data
	    | val );

	while (!((val = nlm_read_nae_reg(nae_base,
	    NAE_REG(block, PHY, (lane_ctrl - PHY_LANE_0_CTRL)))) &
	    PHY_LANE_STAT_PCR));

	/* Clear the Power Down bit */
	val = nlm_read_nae_reg(nae_base, NAE_REG(block, PHY, lane_ctrl));
	val &= ~((1 << 29) | (0x7ffff));
	nlm_write_nae_reg(nae_base, NAE_REG(block, PHY, lane_ctrl),
	    (rext_sel | val));
}