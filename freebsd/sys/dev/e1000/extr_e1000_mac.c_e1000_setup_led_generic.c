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
struct TYPE_4__ {scalar_t__ setup_led; } ;
struct TYPE_6__ {int ledctl_default; int ledctl_mode1; TYPE_1__ ops; } ;
struct TYPE_5__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int E1000_LEDCTL_LED0_BLINK ; 
 int E1000_LEDCTL_LED0_IVRT ; 
 int E1000_LEDCTL_LED0_MODE_MASK ; 
 int E1000_LEDCTL_LED0_MODE_SHIFT ; 
 int E1000_LEDCTL_MODE_LED_OFF ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 

s32 e1000_setup_led_generic(struct e1000_hw *hw)
{
	u32 ledctl;

	DEBUGFUNC("e1000_setup_led_generic");

	if (hw->mac.ops.setup_led != e1000_setup_led_generic)
		return -E1000_ERR_CONFIG;

	if (hw->phy.media_type == e1000_media_type_fiber) {
		ledctl = E1000_READ_REG(hw, E1000_LEDCTL);
		hw->mac.ledctl_default = ledctl;
		/* Turn off LED0 */
		ledctl &= ~(E1000_LEDCTL_LED0_IVRT | E1000_LEDCTL_LED0_BLINK |
			    E1000_LEDCTL_LED0_MODE_MASK);
		ledctl |= (E1000_LEDCTL_MODE_LED_OFF <<
			   E1000_LEDCTL_LED0_MODE_SHIFT);
		E1000_WRITE_REG(hw, E1000_LEDCTL, ledctl);
	} else if (hw->phy.media_type == e1000_media_type_copper) {
		E1000_WRITE_REG(hw, E1000_LEDCTL, hw->mac.ledctl_mode1);
	}

	return E1000_SUCCESS;
}