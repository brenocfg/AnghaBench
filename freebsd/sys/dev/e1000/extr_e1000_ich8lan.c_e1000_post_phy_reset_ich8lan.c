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
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;int /*<<< orphan*/  (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* check_reset_block ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int type; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BM_PORT_GEN_CFG ; 
 int /*<<< orphan*/  BM_WUC_HOST_WU_BIT ; 
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  I82579_LPI_UPDATE_TIMER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  e1000_gate_hw_phy_config_ich8lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_hv_phy_workarounds_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_lv_phy_workarounds_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_oem_bits_config_ich8lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 
#define  e1000_pch2lan 129 
#define  e1000_pchlan 128 
 scalar_t__ e1000_sw_lcd_config_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_write_emi_reg_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub5 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_post_phy_reset_ich8lan(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;
	u16 reg;

	DEBUGFUNC("e1000_post_phy_reset_ich8lan");

	if (hw->phy.ops.check_reset_block(hw))
		return E1000_SUCCESS;

	/* Allow time for h/w to get to quiescent state after reset */
	msec_delay(10);

	/* Perform any necessary post-reset workarounds */
	switch (hw->mac.type) {
	case e1000_pchlan:
		ret_val = e1000_hv_phy_workarounds_ich8lan(hw);
		if (ret_val)
			return ret_val;
		break;
	case e1000_pch2lan:
		ret_val = e1000_lv_phy_workarounds_ich8lan(hw);
		if (ret_val)
			return ret_val;
		break;
	default:
		break;
	}

	/* Clear the host wakeup bit after lcd reset */
	if (hw->mac.type >= e1000_pchlan) {
		hw->phy.ops.read_reg(hw, BM_PORT_GEN_CFG, &reg);
		reg &= ~BM_WUC_HOST_WU_BIT;
		hw->phy.ops.write_reg(hw, BM_PORT_GEN_CFG, reg);
	}

	/* Configure the LCD with the extended configuration region in NVM */
	ret_val = e1000_sw_lcd_config_ich8lan(hw);
	if (ret_val)
		return ret_val;

	/* Configure the LCD with the OEM bits in NVM */
	ret_val = e1000_oem_bits_config_ich8lan(hw, TRUE);

	if (hw->mac.type == e1000_pch2lan) {
		/* Ungate automatic PHY configuration on non-managed 82579 */
		if (!(E1000_READ_REG(hw, E1000_FWSM) &
		    E1000_ICH_FWSM_FW_VALID)) {
			msec_delay(10);
			e1000_gate_hw_phy_config_ich8lan(hw, FALSE);
		}

		/* Set EEE LPI Update Timer to 200usec */
		ret_val = hw->phy.ops.acquire(hw);
		if (ret_val)
			return ret_val;
		ret_val = e1000_write_emi_reg_locked(hw,
						     I82579_LPI_UPDATE_TIMER,
						     0x1387);
		hw->phy.ops.release(hw);
	}

	return ret_val;
}