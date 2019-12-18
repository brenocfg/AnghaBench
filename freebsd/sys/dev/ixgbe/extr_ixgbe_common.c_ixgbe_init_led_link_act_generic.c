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
typedef  int u32 ;
struct ixgbe_mac_info {int led_link_act; int type; } ;
struct ixgbe_hw {struct ixgbe_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_LEDCTL ; 
 int IXGBE_LED_LINK_ACTIVE ; 
 int IXGBE_LED_MODE_MASK_BASE ; 
 int IXGBE_LED_MODE_SHIFT (int) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

s32 ixgbe_init_led_link_act_generic(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;
	u32 led_reg, led_mode;
	u8 i;

	led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);

	/* Get LED link active from the LEDCTL register */
	for (i = 0; i < 4; i++) {
		led_mode = led_reg >> IXGBE_LED_MODE_SHIFT(i);

		if ((led_mode & IXGBE_LED_MODE_MASK_BASE) ==
		     IXGBE_LED_LINK_ACTIVE) {
			mac->led_link_act = i;
			return IXGBE_SUCCESS;
		}
	}

	/*
	 * If LEDCTL register does not have the LED link active set, then use
	 * known MAC defaults.
	 */
	switch (hw->mac.type) {
	case ixgbe_mac_X550EM_a:
	case ixgbe_mac_X550EM_x:
		mac->led_link_act = 1;
		break;
	default:
		mac->led_link_act = 2;
	}
	return IXGBE_SUCCESS;
}