#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_GSSR_I2C_MASK ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_X540 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  ixgbe_set_mux (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

void ixgbe_release_swfw_sync_X550em(struct ixgbe_hw *hw, u32 mask)
{
	DEBUGFUNC("ixgbe_release_swfw_sync_X550em");

	if (mask & IXGBE_GSSR_I2C_MASK)
		ixgbe_set_mux(hw, 0);

	ixgbe_release_swfw_sync_X540(hw, mask);
}