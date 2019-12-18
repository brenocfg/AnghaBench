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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ max_tx_queues; scalar_t__ max_rx_queues; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 scalar_t__ IXGBE_DCA_MAX_QUEUES_82598 ; 
 int /*<<< orphan*/  IXGBE_DCA_RXCTRL (scalar_t__) ; 
 scalar_t__ IXGBE_DCA_RXCTRL_DATA_WRO_EN ; 
 scalar_t__ IXGBE_DCA_RXCTRL_HEAD_WRO_EN ; 
 int /*<<< orphan*/  IXGBE_DCA_TXCTRL (scalar_t__) ; 
 scalar_t__ IXGBE_DCA_TXCTRL_DESC_WRO_EN ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ixgbe_set_pcie_completion_timeout (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_start_hw_generic (struct ixgbe_hw*) ; 

s32 ixgbe_start_hw_82598(struct ixgbe_hw *hw)
{
	u32 regval;
	u32 i;
	s32 ret_val = IXGBE_SUCCESS;

	DEBUGFUNC("ixgbe_start_hw_82598");

	ret_val = ixgbe_start_hw_generic(hw);
	if (ret_val)
		return ret_val;

	/* Disable relaxed ordering */
	for (i = 0; ((i < hw->mac.max_tx_queues) &&
	     (i < IXGBE_DCA_MAX_QUEUES_82598)); i++) {
		regval = IXGBE_READ_REG(hw, IXGBE_DCA_TXCTRL(i));
		regval &= ~IXGBE_DCA_TXCTRL_DESC_WRO_EN;
		IXGBE_WRITE_REG(hw, IXGBE_DCA_TXCTRL(i), regval);
	}

	for (i = 0; ((i < hw->mac.max_rx_queues) &&
	     (i < IXGBE_DCA_MAX_QUEUES_82598)); i++) {
		regval = IXGBE_READ_REG(hw, IXGBE_DCA_RXCTRL(i));
		regval &= ~(IXGBE_DCA_RXCTRL_DATA_WRO_EN |
			    IXGBE_DCA_RXCTRL_HEAD_WRO_EN);
		IXGBE_WRITE_REG(hw, IXGBE_DCA_RXCTRL(i), regval);
	}

	/* set the completion timeout for interface */
	ixgbe_set_pcie_completion_timeout(hw);

	return ret_val;
}