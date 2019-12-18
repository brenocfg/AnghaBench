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
typedef  int u8 ;
struct i40e_hw {int port; } ;
struct ixl_pf {int /*<<< orphan*/  state; int /*<<< orphan*/  dev; struct i40e_hw hw; } ;
struct i40e_lldp_variables {int adminstatus; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  IXL_PF_STATE_FW_LLDP_DISABLED ; 
 int /*<<< orphan*/  atomic_clear_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int i40e_read_lldp_cfg (struct i40e_hw*,struct i40e_lldp_variables*) ; 

int
ixl_get_fw_lldp_status(struct ixl_pf *pf)
{
	enum i40e_status_code ret = I40E_SUCCESS;
	struct i40e_lldp_variables lldp_cfg;
	struct i40e_hw *hw = &pf->hw;
	u8 adminstatus = 0;

	ret = i40e_read_lldp_cfg(hw, &lldp_cfg);
	if (ret)
		return ret;

	/* Get the LLDP AdminStatus for the current port */
	adminstatus = lldp_cfg.adminstatus >> (hw->port * 4);
	adminstatus &= 0xf;

	/* Check if LLDP agent is disabled */
	if (!adminstatus) {
		device_printf(pf->dev, "FW LLDP agent is disabled for this PF.\n");
		atomic_set_int(&pf->state, IXL_PF_STATE_FW_LLDP_DISABLED);
	} else
		atomic_clear_int(&pf->state, IXL_PF_STATE_FW_LLDP_DISABLED);

	return (0);
}