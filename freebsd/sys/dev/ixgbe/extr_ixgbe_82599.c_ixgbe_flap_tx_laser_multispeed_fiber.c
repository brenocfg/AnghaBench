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
struct TYPE_2__ {scalar_t__ autotry_restart; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ ixgbe_check_reset_blocked (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_disable_tx_laser_multispeed_fiber (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_enable_tx_laser_multispeed_fiber (struct ixgbe_hw*) ; 

void ixgbe_flap_tx_laser_multispeed_fiber(struct ixgbe_hw *hw)
{
	DEBUGFUNC("ixgbe_flap_tx_laser_multispeed_fiber");

	/* Blocked by MNG FW so bail */
	if (ixgbe_check_reset_blocked(hw))
		return;

	if (hw->mac.autotry_restart) {
		ixgbe_disable_tx_laser_multispeed_fiber(hw);
		ixgbe_enable_tx_laser_multispeed_fiber(hw);
		hw->mac.autotry_restart = FALSE;
	}
}