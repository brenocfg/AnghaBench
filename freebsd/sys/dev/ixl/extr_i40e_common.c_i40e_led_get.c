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
struct i40e_hw {int dummy; } ;

/* Variables and functions */
#define  I40E_COMBINED_ACTIVITY 131 
#define  I40E_FILTER_ACTIVITY 130 
 int I40E_GLGEN_GPIO_CTL_LED_MODE_MASK ; 
 int I40E_GLGEN_GPIO_CTL_LED_MODE_SHIFT ; 
 int I40E_GLGEN_GPIO_CTL_MAX_INDEX ; 
 int I40E_LED0 ; 
#define  I40E_LINK_ACTIVITY 129 
#define  I40E_MAC_ACTIVITY 128 
 int i40e_led_is_mine (struct i40e_hw*,int) ; 

u32 i40e_led_get(struct i40e_hw *hw)
{
	u32 current_mode = 0;
	u32 mode = 0;
	int i;

	/* as per the documentation GPIO 22-29 are the LED
	 * GPIO pins named LED0..LED7
	 */
	for (i = I40E_LED0; i <= I40E_GLGEN_GPIO_CTL_MAX_INDEX; i++) {
		u32 gpio_val = i40e_led_is_mine(hw, i);

		if (!gpio_val)
			continue;

		/* ignore gpio LED src mode entries related to the activity
		 *  LEDs
		 */
		current_mode = ((gpio_val & I40E_GLGEN_GPIO_CTL_LED_MODE_MASK)
				>> I40E_GLGEN_GPIO_CTL_LED_MODE_SHIFT);
		switch (current_mode) {
		case I40E_COMBINED_ACTIVITY:
		case I40E_FILTER_ACTIVITY:
		case I40E_MAC_ACTIVITY:
		case I40E_LINK_ACTIVITY:
			continue;
		default:
			break;
		}

		mode = (gpio_val & I40E_GLGEN_GPIO_CTL_LED_MODE_MASK) >>
			I40E_GLGEN_GPIO_CTL_LED_MODE_SHIFT;
		break;
	}

	return mode;
}