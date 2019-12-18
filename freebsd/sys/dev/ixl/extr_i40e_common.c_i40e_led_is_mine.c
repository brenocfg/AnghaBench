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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * led; } ;
struct i40e_hw {int port; TYPE_1__ func_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_GLGEN_GPIO_CTL (int) ; 
 int I40E_GLGEN_GPIO_CTL_PRT_NUM_MASK ; 
 int I40E_GLGEN_GPIO_CTL_PRT_NUM_NA_MASK ; 
 int I40E_GLGEN_GPIO_CTL_PRT_NUM_SHIFT ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i40e_led_is_mine(struct i40e_hw *hw, int idx)
{
	u32 gpio_val = 0;
	u32 port;

	if (!hw->func_caps.led[idx])
		return 0;

	gpio_val = rd32(hw, I40E_GLGEN_GPIO_CTL(idx));
	port = (gpio_val & I40E_GLGEN_GPIO_CTL_PRT_NUM_MASK) >>
		I40E_GLGEN_GPIO_CTL_PRT_NUM_SHIFT;

	/* if PRT_NUM_NA is 1 then this LED is not port specific, OR
	 * if it is not our port then ignore
	 */
	if ((gpio_val & I40E_GLGEN_GPIO_CTL_PRT_NUM_NA_MASK) ||
	    (port != hw->port))
		return 0;

	return gpio_val;
}