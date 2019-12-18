#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {scalar_t__ ulp_state; } ;
struct TYPE_10__ {TYPE_4__ ich8lan; } ;
struct TYPE_7__ {int (* acquire ) (struct e1000_hw*) ;int /*<<< orphan*/  (* reset ) (struct e1000_hw*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;} ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct e1000_hw {scalar_t__ device_id; TYPE_5__ dev_spec; TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CV_SMB_CTRL ; 
 int CV_SMB_CTRL_FORCE_SMBUS ; 
 int /*<<< orphan*/  DEBUGOUT1 (char*,int) ; 
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_FORCE_SMBUS ; 
 scalar_t__ E1000_DEV_ID_PCH_I218_LM2 ; 
 scalar_t__ E1000_DEV_ID_PCH_I218_V2 ; 
 scalar_t__ E1000_DEV_ID_PCH_LPT_I217_LM ; 
 scalar_t__ E1000_DEV_ID_PCH_LPT_I217_V ; 
 int E1000_ERR_PHY ; 
 int /*<<< orphan*/  E1000_FEXTNVM7 ; 
 int E1000_FEXTNVM7_DISABLE_SMB_PERST ; 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_ULP_CFG_DONE ; 
 int /*<<< orphan*/  E1000_H2ME ; 
 int E1000_H2ME_ENFORCE_SETTINGS ; 
 int E1000_H2ME_ULP ; 
 int E1000_ICH_FWSM_FW_VALID ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HV_PM_CTRL ; 
 int HV_PM_CTRL_K1_ENABLE ; 
 int /*<<< orphan*/  I218_ULP_CONFIG1 ; 
 int I218_ULP_CONFIG1_DISABLE_SMB_PERST ; 
 int I218_ULP_CONFIG1_DIS_CLR_STICKY_ON_PERST ; 
 int I218_ULP_CONFIG1_EN_ULP_LANPHYPC ; 
 int I218_ULP_CONFIG1_INBAND_EXIT ; 
 int I218_ULP_CONFIG1_IND ; 
 int I218_ULP_CONFIG1_RESET_TO_SMBUS ; 
 int I218_ULP_CONFIG1_START ; 
 int I218_ULP_CONFIG1_STICKY_ULP ; 
 int I218_ULP_CONFIG1_WOL_HOST ; 
 scalar_t__ e1000_pch_lpt ; 
 int e1000_read_phy_reg_hv_locked (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_toggle_lanphypc_pch_lpt (struct e1000_hw*) ; 
 scalar_t__ e1000_ulp_state_off ; 
 int /*<<< orphan*/  e1000_write_phy_reg_hv_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msec_delay (int) ; 
 int stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 

s32 e1000_disable_ulp_lpt_lp(struct e1000_hw *hw, bool force)
{
	s32 ret_val = E1000_SUCCESS;
	u32 mac_reg;
	u16 phy_reg;
	int i = 0;

	if ((hw->mac.type < e1000_pch_lpt) ||
	    (hw->device_id == E1000_DEV_ID_PCH_LPT_I217_LM) ||
	    (hw->device_id == E1000_DEV_ID_PCH_LPT_I217_V) ||
	    (hw->device_id == E1000_DEV_ID_PCH_I218_LM2) ||
	    (hw->device_id == E1000_DEV_ID_PCH_I218_V2) ||
	    (hw->dev_spec.ich8lan.ulp_state == e1000_ulp_state_off))
		return 0;

	if (E1000_READ_REG(hw, E1000_FWSM) & E1000_ICH_FWSM_FW_VALID) {
		if (force) {
			/* Request ME un-configure ULP mode in the PHY */
			mac_reg = E1000_READ_REG(hw, E1000_H2ME);
			mac_reg &= ~E1000_H2ME_ULP;
			mac_reg |= E1000_H2ME_ENFORCE_SETTINGS;
			E1000_WRITE_REG(hw, E1000_H2ME, mac_reg);
		}

		/* Poll up to 300msec for ME to clear ULP_CFG_DONE. */
		while (E1000_READ_REG(hw, E1000_FWSM) &
		       E1000_FWSM_ULP_CFG_DONE) {
			if (i++ == 30) {
				ret_val = -E1000_ERR_PHY;
				goto out;
			}

			msec_delay(10);
		}
		DEBUGOUT1("ULP_CONFIG_DONE cleared after %dmsec\n", i * 10);

		if (force) {
			mac_reg = E1000_READ_REG(hw, E1000_H2ME);
			mac_reg &= ~E1000_H2ME_ENFORCE_SETTINGS;
			E1000_WRITE_REG(hw, E1000_H2ME, mac_reg);
		} else {
			/* Clear H2ME.ULP after ME ULP configuration */
			mac_reg = E1000_READ_REG(hw, E1000_H2ME);
			mac_reg &= ~E1000_H2ME_ULP;
			E1000_WRITE_REG(hw, E1000_H2ME, mac_reg);
		}

		goto out;
	}

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		goto out;

	if (force)
		/* Toggle LANPHYPC Value bit */
		e1000_toggle_lanphypc_pch_lpt(hw);

	/* Unforce SMBus mode in PHY */
	ret_val = e1000_read_phy_reg_hv_locked(hw, CV_SMB_CTRL, &phy_reg);
	if (ret_val) {
		/* The MAC might be in PCIe mode, so temporarily force to
		 * SMBus mode in order to access the PHY.
		 */
		mac_reg = E1000_READ_REG(hw, E1000_CTRL_EXT);
		mac_reg |= E1000_CTRL_EXT_FORCE_SMBUS;
		E1000_WRITE_REG(hw, E1000_CTRL_EXT, mac_reg);

		msec_delay(50);

		ret_val = e1000_read_phy_reg_hv_locked(hw, CV_SMB_CTRL,
						       &phy_reg);
		if (ret_val)
			goto release;
	}
	phy_reg &= ~CV_SMB_CTRL_FORCE_SMBUS;
	e1000_write_phy_reg_hv_locked(hw, CV_SMB_CTRL, phy_reg);

	/* Unforce SMBus mode in MAC */
	mac_reg = E1000_READ_REG(hw, E1000_CTRL_EXT);
	mac_reg &= ~E1000_CTRL_EXT_FORCE_SMBUS;
	E1000_WRITE_REG(hw, E1000_CTRL_EXT, mac_reg);

	/* When ULP mode was previously entered, K1 was disabled by the
	 * hardware.  Re-Enable K1 in the PHY when exiting ULP.
	 */
	ret_val = e1000_read_phy_reg_hv_locked(hw, HV_PM_CTRL, &phy_reg);
	if (ret_val)
		goto release;
	phy_reg |= HV_PM_CTRL_K1_ENABLE;
	e1000_write_phy_reg_hv_locked(hw, HV_PM_CTRL, phy_reg);

	/* Clear ULP enabled configuration */
	ret_val = e1000_read_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, &phy_reg);
	if (ret_val)
		goto release;
	phy_reg &= ~(I218_ULP_CONFIG1_IND |
		     I218_ULP_CONFIG1_STICKY_ULP |
		     I218_ULP_CONFIG1_RESET_TO_SMBUS |
		     I218_ULP_CONFIG1_WOL_HOST |
		     I218_ULP_CONFIG1_INBAND_EXIT |
		     I218_ULP_CONFIG1_EN_ULP_LANPHYPC |
		     I218_ULP_CONFIG1_DIS_CLR_STICKY_ON_PERST |
		     I218_ULP_CONFIG1_DISABLE_SMB_PERST);
	e1000_write_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, phy_reg);

	/* Commit ULP changes by starting auto ULP configuration */
	phy_reg |= I218_ULP_CONFIG1_START;
	e1000_write_phy_reg_hv_locked(hw, I218_ULP_CONFIG1, phy_reg);

	/* Clear Disable SMBus Release on PERST# in MAC */
	mac_reg = E1000_READ_REG(hw, E1000_FEXTNVM7);
	mac_reg &= ~E1000_FEXTNVM7_DISABLE_SMB_PERST;
	E1000_WRITE_REG(hw, E1000_FEXTNVM7, mac_reg);

release:
	hw->phy.ops.release(hw);
	if (force) {
		hw->phy.ops.reset(hw);
		msec_delay(50);
	}
out:
	if (ret_val)
		DEBUGOUT1("Error in ULP disable flow: %d\n", ret_val);
	else
		hw->dev_spec.ich8lan.ulp_state = e1000_ulp_state_off;

	return ret_val;
}