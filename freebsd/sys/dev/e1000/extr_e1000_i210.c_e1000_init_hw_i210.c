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
struct TYPE_5__ {int /*<<< orphan*/  get_cfg_done; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_get_cfg_done_i210 ; 
 int /*<<< orphan*/  e1000_get_flash_presence_i210 (struct e1000_hw*) ; 
 scalar_t__ e1000_i210 ; 
 scalar_t__ e1000_init_hw_82575 (struct e1000_hw*) ; 
 scalar_t__ e1000_pll_workaround_i210 (struct e1000_hw*) ; 

s32 e1000_init_hw_i210(struct e1000_hw *hw)
{
	s32 ret_val;

	DEBUGFUNC("e1000_init_hw_i210");
	if ((hw->mac.type >= e1000_i210) &&
	    !(e1000_get_flash_presence_i210(hw))) {
		ret_val = e1000_pll_workaround_i210(hw);
		if (ret_val != E1000_SUCCESS)
			return ret_val;
	}
	hw->phy.ops.get_cfg_done = e1000_get_cfg_done_i210;
	ret_val = e1000_init_hw_82575(hw);
	return ret_val;
}