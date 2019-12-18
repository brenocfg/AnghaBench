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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_PHY_LED_LINK_MODE_MASK ; 
 int I40E_PHY_LED_MANUAL_ON ; 
 int I40E_PHY_LED_MODE_MASK ; 
 int I40E_PHY_LED_MODE_ORIG ; 
 int I40E_SUCCESS ; 
 int i40e_led_get_reg (struct i40e_hw*,int /*<<< orphan*/ ,int*) ; 
 int i40e_led_set_reg (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

enum i40e_status_code i40e_led_set_phy(struct i40e_hw *hw, bool on,
				       u16 led_addr, u32 mode)
{
	enum i40e_status_code status = I40E_SUCCESS;
	u32 led_ctl = 0;
	u32 led_reg = 0;

	status = i40e_led_get_reg(hw, led_addr, &led_reg);
	if (status)
		return status;
	led_ctl = led_reg;
	if (led_reg & I40E_PHY_LED_LINK_MODE_MASK) {
		led_reg = 0;
		status = i40e_led_set_reg(hw, led_addr, led_reg);
		if (status)
			return status;
	}
	status = i40e_led_get_reg(hw, led_addr, &led_reg);
	if (status)
		goto restore_config;
	if (on)
		led_reg = I40E_PHY_LED_MANUAL_ON;
	else
		led_reg = 0;
	status = i40e_led_set_reg(hw, led_addr, led_reg);
	if (status)
		goto restore_config;
	if (mode & I40E_PHY_LED_MODE_ORIG) {
		led_ctl = (mode & I40E_PHY_LED_MODE_MASK);
		status = i40e_led_set_reg(hw, led_addr, led_ctl);
	}
	return status;

restore_config:
	status = i40e_led_set_reg(hw, led_addr, led_ctl);
	return status;
}