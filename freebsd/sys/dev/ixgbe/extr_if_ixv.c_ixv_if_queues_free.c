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
struct adapter {int num_tx_queues; struct ix_tx_queue* rx_queues; struct ix_tx_queue* tx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct ix_tx_queue*,int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixv_if_queues_free(if_ctx_t ctx)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ix_tx_queue *que = adapter->tx_queues;
	int                i;

	if (que == NULL)
		goto free;

	for (i = 0; i < adapter->num_tx_queues; i++, que++) {
		struct tx_ring *txr = &que->txr;
		if (txr->tx_rsq == NULL)
			break;

		free(txr->tx_rsq, M_DEVBUF);
		txr->tx_rsq = NULL;
	}
	if (adapter->tx_queues != NULL)
		free(adapter->tx_queues, M_DEVBUF);
free:
	if (adapter->rx_queues != NULL)
		free(adapter->rx_queues, M_DEVBUF);
	adapter->tx_queues = NULL;
	adapter->rx_queues = NULL;
}