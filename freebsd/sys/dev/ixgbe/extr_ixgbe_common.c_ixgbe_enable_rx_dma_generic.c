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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int IXGBE_RXCTRL_RXEN ; 
 int /*<<< orphan*/  IXGBE_SUCCESS ; 
 int /*<<< orphan*/  ixgbe_disable_rx (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_enable_rx (struct ixgbe_hw*) ; 

s32 ixgbe_enable_rx_dma_generic(struct ixgbe_hw *hw, u32 regval)
{
	DEBUGFUNC("ixgbe_enable_rx_dma_generic");

	if (regval & IXGBE_RXCTRL_RXEN)
		ixgbe_enable_rx(hw);
	else
		ixgbe_disable_rx(hw);

	return IXGBE_SUCCESS;
}