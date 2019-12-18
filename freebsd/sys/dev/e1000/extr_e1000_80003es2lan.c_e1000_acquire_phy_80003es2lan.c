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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ func; } ;
struct e1000_hw {TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SWFW_PHY0_SM ; 
 int /*<<< orphan*/  E1000_SWFW_PHY1_SM ; 
 int /*<<< orphan*/  e1000_acquire_swfw_sync (struct e1000_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_acquire_phy_80003es2lan(struct e1000_hw *hw)
{
	u16 mask;

	DEBUGFUNC("e1000_acquire_phy_80003es2lan");

	mask = hw->bus.func ? E1000_SWFW_PHY1_SM : E1000_SWFW_PHY0_SM;
	return e1000_acquire_swfw_sync(hw, mask);
}