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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_2__ ops; scalar_t__ autoneg_wait_to_complete; } ;
struct TYPE_4__ {int forced_speed_duplex; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int /*<<< orphan*/ ) ; 
 int E1000_ALL_10_SPEED ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  GG82563_MSCR_ASSERT_CRS_ON_TX ; 
 int /*<<< orphan*/  GG82563_MSCR_TX_CLK_100MBPS_25 ; 
 int /*<<< orphan*/  GG82563_MSCR_TX_CLK_10MBPS_2_5 ; 
 int /*<<< orphan*/  GG82563_MSCR_TX_CLK_MASK ; 
 int /*<<< orphan*/  GG82563_PHY_MAC_SPEC_CTRL ; 
 int /*<<< orphan*/  GG82563_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  GG82563_PSCR_CROSSOVER_MODE_AUTO ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  MII_CR_RESET ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  PHY_FORCE_LIMIT ; 
 int /*<<< orphan*/  e1000_phy_force_speed_duplex_setup (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_phy_has_link_generic (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ e1000_phy_reset_dsp_generic (struct e1000_hw*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static s32 e1000_phy_force_speed_duplex_80003es2lan(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_data;
	bool link;

	DEBUGFUNC("e1000_phy_force_speed_duplex_80003es2lan");

	if (!(hw->phy.ops.read_reg))
		return E1000_SUCCESS;

	/* Clear Auto-Crossover to force MDI manually.  M88E1000 requires MDI
	 * forced whenever speed and duplex are forced.
	 */
	ret_val = hw->phy.ops.read_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_data &= ~GG82563_PSCR_CROSSOVER_MODE_AUTO;
	ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_SPEC_CTRL, phy_data);
	if (ret_val)
		return ret_val;

	DEBUGOUT1("GG82563 PSCR: %X\n", phy_data);

	ret_val = hw->phy.ops.read_reg(hw, PHY_CONTROL, &phy_data);
	if (ret_val)
		return ret_val;

	e1000_phy_force_speed_duplex_setup(hw, &phy_data);

	/* Reset the phy to commit changes. */
	phy_data |= MII_CR_RESET;

	ret_val = hw->phy.ops.write_reg(hw, PHY_CONTROL, phy_data);
	if (ret_val)
		return ret_val;

	usec_delay(1);

	if (hw->phy.autoneg_wait_to_complete) {
		DEBUGOUT("Waiting for forced speed/duplex link on GG82563 phy.\n");

		ret_val = e1000_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						     100000, &link);
		if (ret_val)
			return ret_val;

		if (!link) {
			/* We didn't get link.
			 * Reset the DSP and cross our fingers.
			 */
			ret_val = e1000_phy_reset_dsp_generic(hw);
			if (ret_val)
				return ret_val;
		}

		/* Try once more */
		ret_val = e1000_phy_has_link_generic(hw, PHY_FORCE_LIMIT,
						     100000, &link);
		if (ret_val)
			return ret_val;
	}

	ret_val = hw->phy.ops.read_reg(hw, GG82563_PHY_MAC_SPEC_CTRL,
				       &phy_data);
	if (ret_val)
		return ret_val;

	/* Resetting the phy means we need to verify the TX_CLK corresponds
	 * to the link speed.  10Mbps -> 2.5MHz, else 25MHz.
	 */
	phy_data &= ~GG82563_MSCR_TX_CLK_MASK;
	if (hw->mac.forced_speed_duplex & E1000_ALL_10_SPEED)
		phy_data |= GG82563_MSCR_TX_CLK_10MBPS_2_5;
	else
		phy_data |= GG82563_MSCR_TX_CLK_100MBPS_25;

	/* In addition, we must re-enable CRS on Tx for both half and full
	 * duplex.
	 */
	phy_data |= GG82563_MSCR_ASSERT_CRS_ON_TX;
	ret_val = hw->phy.ops.write_reg(hw, GG82563_PHY_MAC_SPEC_CTRL,
					phy_data);

	return ret_val;
}