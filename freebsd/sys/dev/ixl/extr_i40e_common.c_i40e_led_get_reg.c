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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int flags; int /*<<< orphan*/  port; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQ_PHY_REG_ACCESS_EXTERNAL ; 
 int I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE ; 
 int /*<<< orphan*/  I40E_PHY_COM_REG_PAGE ; 
 int /*<<< orphan*/  I40E_PHY_LED_PROV_REG_1 ; 
 int i40e_aq_get_phy_register (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_get_phy_address (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int i40e_read_phy_register_clause45 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum i40e_status_code i40e_led_get_reg(struct i40e_hw *hw, u16 led_addr,
					      u32 *reg_val)
{
	enum i40e_status_code status;
	u8 phy_addr = 0;

	*reg_val = 0;
	if (hw->flags & I40E_HW_FLAG_AQ_PHY_ACCESS_CAPABLE) {
		status = i40e_aq_get_phy_register(hw,
						I40E_AQ_PHY_REG_ACCESS_EXTERNAL,
						I40E_PHY_COM_REG_PAGE,
						I40E_PHY_LED_PROV_REG_1,
						reg_val, NULL);
	} else {
		phy_addr = i40e_get_phy_address(hw, hw->port);
		status = i40e_read_phy_register_clause45(hw,
							 I40E_PHY_COM_REG_PAGE,
							 led_addr, phy_addr,
							 (u16 *)reg_val);
	}
	return status;
}