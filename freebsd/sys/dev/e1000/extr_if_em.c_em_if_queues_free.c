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
struct tx_ring {struct em_tx_queue* tx_rsq; } ;
struct em_tx_queue {struct tx_ring txr; } ;
struct em_rx_queue {struct tx_ring txr; } ;
struct adapter {int tx_num_queues; struct em_tx_queue* mta; struct em_tx_queue* rx_queues; struct em_tx_queue* tx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  em_release_hw_control (struct adapter*) ; 
 int /*<<< orphan*/  free (struct em_tx_queue*,int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_if_queues_free(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct em_tx_queue *tx_que = adapter->tx_queues;
	struct em_rx_queue *rx_que = adapter->rx_queues;

	if (tx_que != NULL) {
		for (int i = 0; i < adapter->tx_num_queues; i++, tx_que++) {
			struct tx_ring *txr = &tx_que->txr;
			if (txr->tx_rsq == NULL)
				break;

			free(txr->tx_rsq, M_DEVBUF);
			txr->tx_rsq = NULL;
		}
		free(adapter->tx_queues, M_DEVBUF);
		adapter->tx_queues = NULL;
	}

	if (rx_que != NULL) {
		free(adapter->rx_queues, M_DEVBUF);
		adapter->rx_queues = NULL;
	}

	em_release_hw_control(adapter);

	if (adapter->mta != NULL) {
		free(adapter->mta, M_DEVBUF);
	}
}