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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* write_reg_locked ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg_locked ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* acquire ) (struct e1000_hw*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {int id; int revision; TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CV_SMB_CTRL ; 
 int CV_SMB_CTRL_FORCE_SMBUS ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_FORCE_SMBUS ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  PHY_ID1 ; 
 int /*<<< orphan*/  PHY_ID2 ; 
 int PHY_REVISION_MASK ; 
 int TRUE ; 
 scalar_t__ e1000_get_phy_id (struct e1000_hw*) ; 
 scalar_t__ e1000_pch_lpt ; 
 scalar_t__ e1000_set_mdio_slow_mode_hv (struct e1000_hw*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool e1000_phy_is_accessible_pchlan(struct e1000_hw *hw)
{
	u16 phy_reg = 0;
	u32 phy_id = 0;
	s32 ret_val = 0;
	u16 retry_count;
	u32 mac_reg = 0;

	for (retry_count = 0; retry_count < 2; retry_count++) {
		ret_val = hw->phy.ops.read_reg_locked(hw, PHY_ID1, &phy_reg);
		if (ret_val || (phy_reg == 0xFFFF))
			continue;
		phy_id = (u32)(phy_reg << 16);

		ret_val = hw->phy.ops.read_reg_locked(hw, PHY_ID2, &phy_reg);
		if (ret_val || (phy_reg == 0xFFFF)) {
			phy_id = 0;
			continue;
		}
		phy_id |= (u32)(phy_reg & PHY_REVISION_MASK);
		break;
	}

	if (hw->phy.id) {
		if  (hw->phy.id == phy_id)
			goto out;
	} else if (phy_id) {
		hw->phy.id = phy_id;
		hw->phy.revision = (u32)(phy_reg & ~PHY_REVISION_MASK);
		goto out;
	}

	/* In case the PHY needs to be in mdio slow mode,
	 * set slow mode and try to get the PHY id again.
	 */
	if (hw->mac.type < e1000_pch_lpt) {
		hw->phy.ops.release(hw);
		ret_val = e1000_set_mdio_slow_mode_hv(hw);
		if (!ret_val)
			ret_val = e1000_get_phy_id(hw);
		hw->phy.ops.acquire(hw);
	}

	if (ret_val)
		return FALSE;
out:
	if (hw->mac.type >= e1000_pch_lpt) {
		/* Only unforce SMBus if ME is not active */
		if (!(E1000_READ_REG(hw, E1000_FWSM) &
		    E1000_ICH_FWSM_FW_VALID)) {
			/* Unforce SMBus mode in PHY */
			hw->phy.ops.read_reg_locked(hw, CV_SMB_CTRL, &phy_reg);
			phy_reg &= ~CV_SMB_CTRL_FORCE_SMBUS;
			hw->phy.ops.write_reg_locked(hw, CV_SMB_CTRL, phy_reg);

			/* Unforce SMBus mode in MAC */
			mac_reg = E1000_READ_REG(hw, E1000_CTRL_EXT);
			mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
			E1000_WRITE_REG(hw, E1000_CTRL_EXT, mac_reg);
		}
	}

	return TRUE;
}