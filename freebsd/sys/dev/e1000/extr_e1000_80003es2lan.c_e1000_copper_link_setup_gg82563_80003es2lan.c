#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_6__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;scalar_t__ (* commit ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {int mdix; TYPE_3__ ops; scalar_t__ disable_polarity_correction; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* check_mng_mode ) (struct e1000_hw*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int /*<<< orphan*/  E1000_CTRL_EXT_LINK_MODE_MASK ; 
 int E1000_KMRNCTRLSTA_FIFO_CTRL_RX_BYPASS ; 
 int E1000_KMRNCTRLSTA_FIFO_CTRL_TX_BYPASS ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_OFFSET_FIFO_CTRL ; 
 int /*<<< orphan*/  E1000_KMRNCTRLSTA_OFFSET_MAC2PHY_OPMODE ; 
 int E1000_KMRNCTRLSTA_OPMODE_E_IDLE ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GG82563_ICR_DIS_PADDING ; 
 int GG82563_KMCR_PASS_FALSE_CARRIER ; 
 int GG82563_MSCR_ASSERT_CRS_ON_TX ; 
 int GG82563_MSCR_TX_CLK_1000MBPS_25 ; 
 int /*<<< orphan*/  GG82563_PHY_INBAND_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_KMRN_MODE_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_MAC_SPEC_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_PWR_MGMT_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_SPEC_CTRL_2 ; 
 int GG82563_PMCR_ENABLE_ELECTRICAL_IDLE ; 
 int GG82563_PSCR2_REVERSE_AUTO_NEG ; 
 int GG82563_PSCR_CROSSOVER_MODE_AUTO ; 
 int GG82563_PSCR_CROSSOVER_MODE_MASK ; 
 int GG82563_PSCR_CROSSOVER_MODE_MDI ; 
 int GG82563_PSCR_CROSSOVER_MODE_MDIX ; 
 int GG82563_PSCR_POLARITY_REVERSAL_DISABLE ; 
 scalar_t__ e1000_read_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_write_kmrn_reg_80003es2lan (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub10 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub11 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub12 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub13 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub14 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub5 (struct e1000_hw*) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub9 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_copper_link_setup_gg82563_80003es2lan(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u32 reg;
	u16 data;

	DEBUGFUNC("e1000_copper_link_setup_gg82563_80003es2lan");

	ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_MAC_SPEC_CTRL, &data);
	if (ret_val)
		return ret_val;

	data |= GG82563_MSCR_ASSERT_CRS_ON_TX;
	/* Use 25MHz for both link down and 1000Base-T for Tx clock. */
	data |= GG82563_MSCR_TX_CLK_1000MBPS_25;

	ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_MAC_SPEC_CTRL, data);
	if (ret_val)
		return ret_val;

	/* Options:
	 *   MDI/MDI-X = 0 (default)
	 *   0 - Auto for all speeds
	 *   1 - MDI mode
	 *   2 - MDI-X mode
	 *   3 - Auto for 1000Base-T only (MDI-X for 10/100Base-T modes)
	 */
	ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_SPEC_CTRL, &data);
	if (ret_val)
		return ret_val;

	data &= ~GG82563_PSCR_CROSSOVER_MODE_MASK;

	switch (phy->mdix) {
	case 1:
		data |= GG82563_PSCR_CROSSOVER_MODE_MDI;
		break;
	case 2:
		data |= GG82563_PSCR_CROSSOVER_MODE_MDIX;
		break;
	case 0:
	default:
		data |= GG82563_PSCR_CROSSOVER_MODE_AUTO;
		break;
	}

	/* Options:
	 *   disable_polarity_correction = 0 (default)
	 *       Automatic Correction for Reversed Cable Polarity
	 *   0 - Disabled
	 *   1 - Enabled
	 */
	data &= ~GG82563_PSCR_POLARITY_REVERSAL_DISABLE;
	if (phy->disable_polarity_correction)
		data |= GG82563_PSCR_POLARITY_REVERSAL_DISABLE;

	ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_SPEC_CTRL, data);
	if (ret_val)
		return ret_val;

	/* SW Reset the PHY so all changes take effect */
	ret_val = hw->phy.ops.commit(hw);
	if (ret_val) {
		DEBUGOUT("Error Resetting the PHY\n");
		return ret_val;
	}

	/* Bypass Rx and Tx FIFO's */
	reg = E1000_KMRNCTRLSTA_OFFSET_FIFO_CTRL;
	data = (E1000_KMRNCTRLSTA_FIFO_CTRL_RX_BYPASS |
		E1000_KMRNCTRLSTA_FIFO_CTRL_TX_BYPASS);
	ret_val = e1000_write_kmrn_reg_80003es2lan(hw, reg, data);
	if (ret_val)
		return ret_val;

	reg = E1000_KMRNCTRLSTA_OFFSET_MAC2PHY_OPMODE;
	ret_val = e1000_read_kmrn_reg_80003es2lan(hw, reg, &data);
	if (ret_val)
		return ret_val;
	data |= E1000_KMRNCTRLSTA_OPMODE_E_IDLE;
	ret_val = e1000_write_kmrn_reg_80003es2lan(hw, reg, data);
	if (ret_val)
		return ret_val;

	ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_SPEC_CTRL_2, &data);
	if (ret_val)
		return ret_val;

	data &= ~GG82563_PSCR2_REVERSE_AUTO_NEG;
	ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_SPEC_CTRL_2, data);
	if (ret_val)
		return ret_val;

	reg = E1000_READ_REG(hw, E1000_CTRL_EXT);
	reg &= ~E1000_CTRL_EXT_LINK_MODE_MASK;
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, reg);

	ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_PWR_MGMT_CTRL, &data);
	if (ret_val)
		return ret_val;

	/* Do not init these registers when the HW is in IAMT mode, since the
	 * firmware will have already initialized them.  We only initialize
	 * them if the HW is not in IAMT mode.
	 */
	if (!hw->mac.ops.check_mng_mode(hw)) {
		/* Enable Electrical Idle on the PHY */
		data |= GG82563_PMCR_ENABLE_ELECTRICAL_IDLE;
		ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_PWR_MGMT_CTRL,
						data);
		if (ret_val)
			return ret_val;

		ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_KMRN_MODE_CTRL,
					       &data);
		if (ret_val)
			return ret_val;

		data &= ~GG82563_KMCR_PASS_FALSE_CARRIER;
		ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_KMRN_MODE_CTRL,
						data);
		if (ret_val)
			return ret_val;
	}

	/* Workaround: Disable padding in Kumeran interface in the MAC
	 * and in the PHY to avoid CRC errors.
	 */
	ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_INBAND_CTRL, &data);
	if (ret_val)
		return ret_val;

	data |= GG82563_ICR_DIS_PADDING;
	ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_INBAND_CTRL, data);
	if (ret_val)
		return ret_val;

	return E1000_SUCCESS;
}