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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_sec_rx_path ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* disable_sec_rx_path ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_RXCTRL_RXEN ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_disable_rx (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_enable_rx (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 

s32 ixgbe_enable_rx_dma_82599(struct ixgbe_hw *hw, u32 regval)
{

	DEBUGFUNC("ixgbe_enable_rx_dma_82599");

	/*
	 * Workaround for 82599 silicon errata when enabling the Rx datapath.
	 * If traffic is incoming before we enable the Rx unit, it could hang
	 * the Rx DMA unit.  Therefore, make sure the security engine is
	 * completely disabled prior to enabling the Rx unit.
	 */

	hw->mac.ops.disable_sec_rx_path(hw);

	if (regval & IXGBE_RXCTRL_RXEN)
		ixgbe_enable_rx(hw);
	else
		ixgbe_disable_rx(hw);

	hw->mac.ops.enable_sec_rx_path(hw);

	return IXGBE_SUCCESS;
}