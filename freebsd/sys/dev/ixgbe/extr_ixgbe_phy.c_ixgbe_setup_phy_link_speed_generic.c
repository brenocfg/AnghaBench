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
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_10_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int IXGBE_LINK_SPEED_2_5GB_FULL ; 
 int IXGBE_LINK_SPEED_5GB_FULL ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_1PARAMETER (int) ; 
 int /*<<< orphan*/  ixgbe_setup_phy_link (struct ixgbe_hw*) ; 

s32 ixgbe_setup_phy_link_speed_generic(struct ixgbe_hw *hw,
				       ixgbe_link_speed speed,
				       bool autoneg_wait_to_complete)
{
	UNREFERENCED_1PARAMETER(autoneg_wait_to_complete);

	DEBUGFUNC("ixgbe_setup_phy_link_speed_generic");

	/*
	 * Clear autoneg_advertised and set new values based on input link
	 * speed.
	 */
	hw->phy.autoneg_advertised = 0;

	if (speed & IXGBE_LINK_SPEED_10GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_10GB_FULL;

	if (speed & IXGBE_LINK_SPEED_5GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_5GB_FULL;

	if (speed & IXGBE_LINK_SPEED_2_5GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_2_5GB_FULL;

	if (speed & IXGBE_LINK_SPEED_1GB_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_1GB_FULL;

	if (speed & IXGBE_LINK_SPEED_100_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_100_FULL;

	if (speed & IXGBE_LINK_SPEED_10_FULL)
		hw->phy.autoneg_advertised |= IXGBE_LINK_SPEED_10_FULL;

	/* Setup link based on the new speed settings */
	ixgbe_setup_phy_link(hw);

	return IXGBE_SUCCESS;
}