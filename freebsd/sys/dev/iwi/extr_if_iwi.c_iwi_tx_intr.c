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
typedef  scalar_t__ uint32_t ;
struct iwi_tx_ring {scalar_t__ next; int /*<<< orphan*/  queued; int /*<<< orphan*/  data_dmat; struct iwi_tx_data* data; int /*<<< orphan*/  csr_ridx; } ;
struct iwi_tx_data {int /*<<< orphan*/ * m; int /*<<< orphan*/ * ni; int /*<<< orphan*/  map; } ;
struct iwi_softc {scalar_t__ sc_softled; scalar_t__ sc_tx_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ CSR_READ_4 (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  IWI_LED_TX ; 
 int IWI_TX_RING_COUNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_led_event (struct iwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_start (struct iwi_softc*) ; 

__attribute__((used)) static void
iwi_tx_intr(struct iwi_softc *sc, struct iwi_tx_ring *txq)
{
	struct iwi_tx_data *data;
	uint32_t hw;

	hw = CSR_READ_4(sc, txq->csr_ridx);

	while (txq->next != hw) {
		data = &txq->data[txq->next];
		DPRINTFN(15, ("tx done idx=%u\n", txq->next));
		bus_dmamap_sync(txq->data_dmat, data->map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(txq->data_dmat, data->map);
		ieee80211_tx_complete(data->ni, data->m, 0);
		data->ni = NULL;
		data->m = NULL;
		txq->queued--;
		txq->next = (txq->next + 1) % IWI_TX_RING_COUNT;
	}
	sc->sc_tx_timer = 0;
	if (sc->sc_softled)
		iwi_led_event(sc, IWI_LED_TX);
	iwi_start(sc);
}