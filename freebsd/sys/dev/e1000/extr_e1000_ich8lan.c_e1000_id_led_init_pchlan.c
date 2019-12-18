#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct e1000_mac_info {int ledctl_default; int ledctl_mode1; int ledctl_mode2; } ;
struct TYPE_3__ {scalar_t__ (* valid_led_default ) (struct e1000_hw*,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ nvm; struct e1000_mac_info mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_LEDCTL ; 
 int E1000_LEDCTL_LED0_MODE_MASK ; 
 int E1000_LEDCTL_MODE_LINK_UP ; 
 int E1000_PHY_LED0_IVRT ; 
 int E1000_PHY_LED0_MASK ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ E1000_SUCCESS ; 
#define  ID_LED_DEF1_OFF2 135 
#define  ID_LED_DEF1_ON2 134 
#define  ID_LED_OFF1_DEF2 133 
#define  ID_LED_OFF1_OFF2 132 
#define  ID_LED_OFF1_ON2 131 
#define  ID_LED_ON1_DEF2 130 
#define  ID_LED_ON1_OFF2 129 
#define  ID_LED_ON1_ON2 128 
 scalar_t__ stub1 (struct e1000_hw*,int*) ; 

__attribute__((used)) static s32 e1000_id_led_init_pchlan(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	s32 ret_val;
	const u32 ledctl_on = E1000_LEDCTL_MODE_LINK_UP;
	const u32 ledctl_off = E1000_LEDCTL_MODE_LINK_UP | E1000_PHY_LED0_IVRT;
	u16 data, i, temp, shift;

	DEBUGFUNC("e1000_id_led_init_pchlan");

	/* Get default ID LED modes */
	ret_val = hw->nvm.ops.valid_led_default(hw, &data);
	if (ret_val)
		return ret_val;

	mac->ledctl_default = E1000_READ_REG(hw, E1000_LEDCTL);
	mac->ledctl_mode1 = mac->ledctl_default;
	mac->ledctl_mode2 = mac->ledctl_default;

	for (i = 0; i < 4; i++) {
		temp = (data >> (i << 2)) & E1000_LEDCTL_LED0_MODE_MASK;
		shift = (i * 5);
		switch (temp) {
		case ID_LED_ON1_DEF2:
		case ID_LED_ON1_ON2:
		case ID_LED_ON1_OFF2:
			mac->ledctl_mode1 &= ~(E1000_PHY_LED0_MASK << shift);
			mac->ledctl_mode1 |= (ledctl_on << shift);
			break;
		case ID_LED_OFF1_DEF2:
		case ID_LED_OFF1_ON2:
		case ID_LED_OFF1_OFF2:
			mac->ledctl_mode1 &= ~(E1000_PHY_LED0_MASK << shift);
			mac->ledctl_mode1 |= (ledctl_off << shift);
			break;
		default:
			/* Do nothing */
			break;
		}
		switch (temp) {
		case ID_LED_DEF1_ON2:
		case ID_LED_ON1_ON2:
		case ID_LED_OFF1_ON2:
			mac->ledctl_mode2 &= ~(E1000_PHY_LED0_MASK << shift);
			mac->ledctl_mode2 |= (ledctl_on << shift);
			break;
		case ID_LED_DEF1_OFF2:
		case ID_LED_ON1_OFF2:
		case ID_LED_OFF1_OFF2:
			mac->ledctl_mode2 &= ~(E1000_PHY_LED0_MASK << shift);
			mac->ledctl_mode2 |= (ledctl_off << shift);
			break;
		default:
			/* Do nothing */
			break;
		}
	}

	return E1000_SUCCESS;
}