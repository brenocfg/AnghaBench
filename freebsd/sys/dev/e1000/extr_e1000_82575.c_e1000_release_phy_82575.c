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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct e1000_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {scalar_t__ func; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_1__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ E1000_FUNC_1 ; 
 scalar_t__ E1000_FUNC_2 ; 
 scalar_t__ E1000_FUNC_3 ; 
 int /*<<< orphan*/  E1000_SWFW_PHY0_SM ; 
 int /*<<< orphan*/  E1000_SWFW_PHY1_SM ; 
 int /*<<< orphan*/  E1000_SWFW_PHY2_SM ; 
 int /*<<< orphan*/  E1000_SWFW_PHY3_SM ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_release_phy_82575(struct e1000_hw *hw)
{
	u16 mask = E1000_SWFW_PHY0_SM;

	DEBUGFUNC("e1000_release_phy_82575");

	if (hw->bus.func == E1000_FUNC_1)
		mask = E1000_SWFW_PHY1_SM;
	else if (hw->bus.func == E1000_FUNC_2)
		mask = E1000_SWFW_PHY2_SM;
	else if (hw->bus.func == E1000_FUNC_3)
		mask = E1000_SWFW_PHY3_SM;

	hw->mac.ops.release_swfw_sync(hw, mask);
}