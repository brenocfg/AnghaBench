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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ func; } ;
struct ixgbe_hw {int wol_enabled; TYPE_1__ bus; } ;
struct adapter {int wol_support; int /*<<< orphan*/  wufc; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBE_DEVICE_CAPS_WOL_PORT0 ; 
 int IXGBE_DEVICE_CAPS_WOL_PORT0_1 ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WUFC ; 
 int /*<<< orphan*/  ixgbe_get_device_caps (struct ixgbe_hw*,int*) ; 

__attribute__((used)) static void
ixgbe_check_wol_support(struct adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u16             dev_caps = 0;

	/* Find out WoL support for port */
	adapter->wol_support = hw->wol_enabled = 0;
	ixgbe_get_device_caps(hw, &dev_caps);
	if ((dev_caps & IXGBE_DEVICE_CAPS_WOL_PORT0_1) ||
	    ((dev_caps & IXGBE_DEVICE_CAPS_WOL_PORT0) &&
	     hw->bus.func == 0))
		adapter->wol_support = hw->wol_enabled = 1;

	/* Save initial wake up filter configuration */
	adapter->wufc = IXGBE_READ_REG(hw, IXGBE_WUFC);

	return;
}