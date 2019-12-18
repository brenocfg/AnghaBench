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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  addr; } ;
struct ixgbe_hw {TYPE_1__ mac; void* adapter_stopped; } ;
struct adapter {struct ixgbe_hw hw; void* link_up; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_RAH_AV ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_disable_tx_laser (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_if_update_admin_status (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_82599EB ; 
 int /*<<< orphan*/  ixgbe_reset_hw (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_set_rar (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_stop_adapter (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_stop_mac_link_on_d3_82599 (struct ixgbe_hw*) ; 

__attribute__((used)) static void
ixgbe_if_stop(if_ctx_t ctx)
{
	struct adapter  *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw *hw = &adapter->hw;

	INIT_DEBUGOUT("ixgbe_if_stop: begin\n");

	ixgbe_reset_hw(hw);
	hw->adapter_stopped = FALSE;
	ixgbe_stop_adapter(hw);
	if (hw->mac.type == ixgbe_mac_82599EB)
		ixgbe_stop_mac_link_on_d3_82599(hw);
	/* Turn off the laser - noop with no optics */
	ixgbe_disable_tx_laser(hw);

	/* Update the stack */
	adapter->link_up = FALSE;
	ixgbe_if_update_admin_status(ctx);

	/* reprogram the RAR[0] in case user changed it. */
	ixgbe_set_rar(&adapter->hw, 0, adapter->hw.mac.addr, 0, IXGBE_RAH_AV);

	return;
}