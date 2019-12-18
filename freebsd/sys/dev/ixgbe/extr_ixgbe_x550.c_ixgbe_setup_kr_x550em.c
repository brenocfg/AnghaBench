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
struct TYPE_2__ {int autoneg_advertised; } ;
struct ixgbe_hw {TYPE_1__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_LINK_SPEED_2_5GB_FULL ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 scalar_t__ ixgbe_check_reset_blocked (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_setup_kr_speed_x550em (struct ixgbe_hw*,int) ; 

s32 ixgbe_setup_kr_x550em(struct ixgbe_hw *hw)
{
	/* leave link alone for 2.5G */
	if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_2_5GB_FULL)
		return IXGBE_SUCCESS;

	if (ixgbe_check_reset_blocked(hw))
		return 0;

	return ixgbe_setup_kr_speed_x550em(hw, hw->phy.autoneg_advertised);
}