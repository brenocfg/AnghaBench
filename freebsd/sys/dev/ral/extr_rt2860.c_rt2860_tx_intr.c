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
typedef  size_t uint32_t ;
struct rt2860_tx_ring {size_t next; int queued; struct rt2860_tx_data** data; } ;
struct rt2860_tx_data {int /*<<< orphan*/ * m; int /*<<< orphan*/ * ni; int /*<<< orphan*/  map; } ;
struct rt2860_softc {int qfullmsk; scalar_t__ sc_tx_timer; int /*<<< orphan*/  data_pool; int /*<<< orphan*/  txwi_dmat; struct rt2860_tx_ring* txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 size_t RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT2860_TX_DTX_IDX (int) ; 
 int RT2860_TX_RING_COUNT ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct rt2860_tx_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  rt2860_drain_stats_fifo (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_start (struct rt2860_softc*) ; 

__attribute__((used)) static void
rt2860_tx_intr(struct rt2860_softc *sc, int qid)
{
	struct rt2860_tx_ring *ring = &sc->txq[qid];
	uint32_t hw;

	rt2860_drain_stats_fifo(sc);

	hw = RAL_READ(sc, RT2860_TX_DTX_IDX(qid));
	while (ring->next != hw) {
		struct rt2860_tx_data *data = ring->data[ring->next];

		if (data != NULL) {
			bus_dmamap_sync(sc->txwi_dmat, data->map,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->txwi_dmat, data->map);
			ieee80211_tx_complete(data->ni, data->m, 0);
			data->ni = NULL;
			data->m = NULL;
			SLIST_INSERT_HEAD(&sc->data_pool, data, next);
			ring->data[ring->next] = NULL;
		}
		ring->queued--;
		ring->next = (ring->next + 1) % RT2860_TX_RING_COUNT;
	}

	sc->sc_tx_timer = 0;
	if (ring->queued < RT2860_TX_RING_COUNT)
		sc->qfullmsk &= ~(1 << qid);
	rt2860_start(sc);
}