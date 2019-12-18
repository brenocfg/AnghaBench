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
struct ix_rx_queue {int /*<<< orphan*/  msix; } ;
struct adapter {scalar_t__ num_rx_queues; scalar_t__ num_tx_queues; int /*<<< orphan*/  vector; int /*<<< orphan*/  hw; struct ix_rx_queue* rx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_EITR_DEFAULT ; 
 int /*<<< orphan*/  IXGBE_VTEITR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  ixv_set_ivar (struct adapter*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixv_configure_ivars(struct adapter *adapter)
{
	struct ix_rx_queue *que = adapter->rx_queues;

	MPASS(adapter->num_rx_queues == adapter->num_tx_queues);

	for (int i = 0; i < adapter->num_rx_queues; i++, que++) {
		/* First the RX queue entry */
		ixv_set_ivar(adapter, i, que->msix, 0);
		/* ... and the TX */
		ixv_set_ivar(adapter, i, que->msix, 1);
		/* Set an initial value in EITR */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_VTEITR(que->msix),
		    IXGBE_EITR_DEFAULT);
	}

	/* For the mailbox interrupt */
	ixv_set_ivar(adapter, 1, adapter->vector, -1);
}