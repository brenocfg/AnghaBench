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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ e1000_cfg_kmrn_1000_80003es2lan (struct e1000_hw*) ; 
 scalar_t__ e1000_cfg_kmrn_10_100_80003es2lan (struct e1000_hw*,scalar_t__) ; 
 scalar_t__ e1000_get_speed_and_duplex_copper_generic (struct e1000_hw*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ e1000_media_type_copper ; 

__attribute__((used)) static s32 e1000_cfg_on_link_up_80003es2lan(struct e1000_hw *hw)
{
	s32 ret_val = E1000_SUCCESS;
	u16 speed;
	u16 duplex;

	DEBUGFUNC("e1000_configure_on_link_up");

	if (hw->phy.media_type == e1000_media_type_copper) {
		ret_val = e1000_get_speed_and_duplex_copper_generic(hw, &speed,
								    &duplex);
		if (ret_val)
			return ret_val;

		if (speed == SPEED_1000)
			ret_val = e1000_cfg_kmrn_1000_80003es2lan(hw);
		else
			ret_val = e1000_cfg_kmrn_10_100_80003es2lan(hw, duplex);
	}

	return ret_val;
}