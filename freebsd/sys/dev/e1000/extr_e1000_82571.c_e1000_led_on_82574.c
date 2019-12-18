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
struct TYPE_2__ {int ledctl_mode2; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int E1000_LEDCTL_LED0_IVRT ; 
 int E1000_LEDCTL_MODE_LED_ON ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_led_on_82574(struct e1000_hw *hw)
{
	u32 ctrl;
	u32 i;

	DEBUGFUNC("e1000_led_on_82574");

	ctrl = hw->mac.ledctl_mode2;
	if (!(E1000_STATUS_LU & E1000_READ_REG(hw, E1000_STATUS))) {
		/* If no link, then turn LED on by setting the invert bit
		 * for each LED that's "on" (0x0E) in ledctl_mode2.
		 */
		for (i = 0; i < 4; i++)
			if (((hw->mac.ledctl_mode2 >> (i * 8)) & 0xFF) ==
			    E1000_LEDCTL_MODE_LED_ON)
				ctrl |= (E1000_LEDCTL_LED0_IVRT << (i * 8));
	}
	E1000_WRITE_REG(hw, E1000_LEDCTL, ctrl);

	return E1000_SUCCESS;
}