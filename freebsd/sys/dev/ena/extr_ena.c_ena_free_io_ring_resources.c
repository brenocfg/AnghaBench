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
struct ena_ring {int /*<<< orphan*/  ring_mtx; int /*<<< orphan*/  br; int /*<<< orphan*/  rx_stats; int /*<<< orphan*/  tx_stats; } ;
struct ena_adapter {struct ena_ring* rx_ring; struct ena_ring* tx_ring; } ;
typedef  int /*<<< orphan*/  counter_u64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_RING_MTX_LOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  ENA_RING_MTX_UNLOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  drbr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_free_counters (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ena_free_io_ring_resources(struct ena_adapter *adapter, unsigned int qid)
{
	struct ena_ring *txr = &adapter->tx_ring[qid];
	struct ena_ring *rxr = &adapter->rx_ring[qid];

	ena_free_counters((counter_u64_t *)&txr->tx_stats,
	    sizeof(txr->tx_stats));
	ena_free_counters((counter_u64_t *)&rxr->rx_stats,
	    sizeof(rxr->rx_stats));

	ENA_RING_MTX_LOCK(txr);
	drbr_free(txr->br, M_DEVBUF);
	ENA_RING_MTX_UNLOCK(txr);

	mtx_destroy(&txr->ring_mtx);
}