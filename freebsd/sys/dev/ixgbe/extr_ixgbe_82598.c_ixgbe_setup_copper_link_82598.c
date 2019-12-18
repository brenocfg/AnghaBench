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
struct TYPE_3__ {int /*<<< orphan*/  (* setup_link_speed ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  ixgbe_start_mac_link_82598 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_setup_copper_link_82598(struct ixgbe_hw *hw,
					 ixgbe_link_speed speed,
					 bool autoneg_wait_to_complete)
{
	s32 status;

	DEBUGFUNC("ixgbe_setup_copper_link_82598");

	/* Setup the PHY according to input speed */
	status = hw->phy.ops.setup_link_speed(hw, speed,
					      autoneg_wait_to_complete);
	/* Set up MAC */
	ixgbe_start_mac_link_82598(hw, autoneg_wait_to_complete);

	return status;
}