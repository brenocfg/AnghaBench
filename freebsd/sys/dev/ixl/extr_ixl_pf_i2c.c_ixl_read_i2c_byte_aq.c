#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_1__ aq; } ;
struct ixl_pf {struct i40e_hw hw; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE ; 
 scalar_t__ I40E_SUCCESS ; 
 int /*<<< orphan*/  IXL_DBG_I2C ; 
 scalar_t__ i40e_aq_get_phy_register (struct i40e_hw*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ixl_dbg (struct ixl_pf*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32
ixl_read_i2c_byte_aq(struct ixl_pf *pf, u8 byte_offset,
		  u8 dev_addr, u8 *data)
{
	struct i40e_hw *hw = &pf->hw;
	s32 status = I40E_SUCCESS;
	u32 reg;

	status = i40e_aq_get_phy_register(hw,
					I40E_AQ_PHY_REG_ACCESS_EXTERNAL_MODULE,
					dev_addr,
					byte_offset,
					&reg, NULL);

	if (status)
		ixl_dbg(pf, IXL_DBG_I2C, "I2C byte read status %s, error %s\n",
		    i40e_stat_str(hw, status), i40e_aq_str(hw, hw->aq.asq_last_status));
	else
		*data = (u8)reg;

	return status;
}