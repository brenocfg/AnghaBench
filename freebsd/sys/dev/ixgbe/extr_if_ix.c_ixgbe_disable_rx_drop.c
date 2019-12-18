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
typedef  int u32 ;
struct rx_ring {int /*<<< orphan*/  me; } ;
struct ixgbe_hw {int dummy; } ;
struct adapter {int num_rx_queues; int num_vfs; TYPE_1__* rx_queues; struct ixgbe_hw hw; } ;
struct TYPE_2__ {struct rx_ring rxr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_QDE ; 
 int IXGBE_QDE_IDX_SHIFT ; 
 int IXGBE_QDE_WRITE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SRRCTL (int /*<<< orphan*/ ) ; 
 int IXGBE_SRRCTL_DROP_EN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixgbe_disable_rx_drop(struct adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct rx_ring  *rxr;
	u32             srrctl;

	for (int i = 0; i < adapter->num_rx_queues; i++) {
		rxr = &adapter->rx_queues[i].rxr;
		srrctl = IXGBE_READ_REG(hw, IXGBE_SRRCTL(rxr->me));
		srrctl &= ~IXGBE_SRRCTL_DROP_EN;
		IXGBE_WRITE_REG(hw, IXGBE_SRRCTL(rxr->me), srrctl);
	}

	/* disable drop for each vf */
	for (int i = 0; i < adapter->num_vfs; i++) {
		IXGBE_WRITE_REG(hw, IXGBE_QDE,
		    (IXGBE_QDE_WRITE | (i << IXGBE_QDE_IDX_SHIFT)));
	}
}