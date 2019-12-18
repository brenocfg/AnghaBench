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
struct tx_ring {struct ix_tx_queue* tx_rsq; } ;
struct ix_tx_queue {struct tx_ring txr; } ;
struct ix_rx_queue {struct tx_ring txr; } ;
struct adapter {int num_tx_queues; struct ix_tx_queue* rx_queues; struct ix_tx_queue* tx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_IXGBE ; 
 int /*<<< orphan*/  free (struct ix_tx_queue*,int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgbe_if_queues_free(if_ctx_t ctx)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ix_tx_queue *tx_que = adapter->tx_queues;
	struct ix_rx_queue *rx_que = adapter->rx_queues;
	int                i;

	if (tx_que != NULL) {
		for (i = 0; i < adapter->num_tx_queues; i++, tx_que++) {
			struct tx_ring *txr = &tx_que->txr;
			if (txr->tx_rsq == NULL)
				break;

			free(txr->tx_rsq, M_IXGBE);
			txr->tx_rsq = NULL;
		}

		free(adapter->tx_queues, M_IXGBE);
		adapter->tx_queues = NULL;
	}
	if (rx_que != NULL) {
		free(adapter->rx_queues, M_IXGBE);
		adapter->rx_queues = NULL;
	}
}