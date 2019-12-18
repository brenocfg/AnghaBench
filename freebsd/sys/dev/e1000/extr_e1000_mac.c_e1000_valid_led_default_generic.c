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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct e1000_hw*,int /*<<< orphan*/ ,int,scalar_t__*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ ID_LED_DEFAULT ; 
 scalar_t__ ID_LED_RESERVED_0000 ; 
 scalar_t__ ID_LED_RESERVED_FFFF ; 
 int /*<<< orphan*/  NVM_ID_LED_SETTINGS ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int,scalar_t__*) ; 

s32 e1000_valid_led_default_generic(struct e1000_hw *hw, u16 *data)
{
	s32 ret_val;

	DEBUGFUNC("e1000_valid_led_default_generic");

	ret_val = hw->nvm.ops.read(hw, NVM_ID_LED_SETTINGS, 1, data);
	if (ret_val) {
		DEBUGOUT("NVM Read Error\n");
		return ret_val;
	}

	if (*data == ID_LED_RESERVED_0000 || *data == ID_LED_RESERVED_FFFF)
		*data = ID_LED_DEFAULT;

	return E1000_SUCCESS;
}