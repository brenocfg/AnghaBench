#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* set_d0_lplu_state ) (struct e1000_hw*,int /*<<< orphan*/ ) ;scalar_t__ (* set_d3_lplu_state ) (struct e1000_hw*,int /*<<< orphan*/ ) ;scalar_t__ (* reset ) (struct e1000_hw*) ;} ;
struct e1000_phy_info {scalar_t__ type; int mdix; scalar_t__ autoneg_advertised; TYPE_2__ ops; } ;
struct TYPE_3__ {scalar_t__ autoneg; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ ADVERTISE_1000_FULL ; 
 int /*<<< orphan*/  CR_1000T_MS_ENABLE ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CONFIG ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CTRL ; 
 int /*<<< orphan*/  IGP01E1000_PSCFR_SMART_SPEED ; 
 int /*<<< orphan*/  IGP01E1000_PSCR_AUTO_MDIX ; 
 int /*<<< orphan*/  IGP01E1000_PSCR_FORCE_MDI_MDIX ; 
 int /*<<< orphan*/  PHY_1000T_CTRL ; 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_set_master_slave_mode (struct e1000_hw*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub9 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 e1000_copper_link_setup_igp(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 data;

	DEBUGFUNC("e1000_copper_link_setup_igp");


	ret_val = hw->phy.ops.reset(hw);
	if (ret_val) {
		DEBUGOUT("Error resetting the PHY.\n");
		return ret_val;
	}

	/* Wait 100ms for MAC to configure PHY from NVM settings, to avoid
	 * timeout issues when LFS is enabled.
	 */
	msec_delay(100);

	/* The NVM settings will configure LPLU in D3 for
	 * non-IGP1 PHYs.
	 */
	if (phy->type == e1000_phy_igp) {
		/* disable lplu d3 during driver init */
		ret_val = hw->phy.ops.set_d3_lplu_state(hw, FALSE);
		if (ret_val) {
			DEBUGOUT("Error Disabling LPLU D3\n");
			return ret_val;
		}
	}

	/* disable lplu d0 during driver init */
	if (hw->phy.ops.set_d0_lplu_state) {
		ret_val = hw->phy.ops.set_d0_lplu_state(hw, FALSE);
		if (ret_val) {
			DEBUGOUT("Error Disabling LPLU D0\n");
			return ret_val;
		}
	}
	/* Configure mdi-mdix settings */
	ret_val = phy->ops.read_reg(hw, IGP01E1000_PHY_PORT_CTRL, &data);
	if (ret_val)
		return ret_val;

	data &= ~IGP01E1000_PSCR_AUTO_MDIX;

	switch (phy->mdix) {
	case 1:
		data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;
		break;
	case 2:
		data |= IGP01E1000_PSCR_FORCE_MDI_MDIX;
		break;
	case 0:
	default:
		data |= IGP01E1000_PSCR_AUTO_MDIX;
		break;
	}
	ret_val = phy->ops.write_reg(hw, IGP01E1000_PHY_PORT_CTRL, data);
	if (ret_val)
		return ret_val;

	/* set auto-master slave resolution settings */
	if (hw->mac.autoneg) {
		/* when autonegotiation advertisement is only 1000Mbps then we
		 * should disable SmartSpeed and enable Auto MasterSlave
		 * resolution as hardware default.
		 */
		if (phy->autoneg_advertised == ADVERTISE_1000_FULL) {
			/* Disable SmartSpeed */
			ret_val = phy->ops.read_reg(hw,
						    IGP01E1000_PHY_PORT_CONFIG,
						    &data);
			if (ret_val)
				return ret_val;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			if (ret_val)
				return ret_val;

			/* Set auto Master/Slave resolution process */
			ret_val = phy->ops.read_reg(hw, PHY_1000T_CTRL, &data);
			if (ret_val)
				return ret_val;

			data &= ~CR_1000T_MS_ENABLE;
			ret_val = phy->ops.write_reg(hw, PHY_1000T_CTRL, data);
			if (ret_val)
				return ret_val;
		}

		ret_val = e1000_set_master_slave_mode(hw);
	}

	return ret_val;
}