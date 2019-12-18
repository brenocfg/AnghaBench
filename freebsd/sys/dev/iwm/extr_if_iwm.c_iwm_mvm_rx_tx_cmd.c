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
struct mbuf {int dummy; } ;
struct iwm_tx_ring {scalar_t__ queued; int /*<<< orphan*/  data_dmat; struct iwm_tx_data* data; } ;
struct iwm_tx_data {int done; struct iwm_node* in; struct mbuf* m; int /*<<< orphan*/  map; } ;
struct iwm_softc {int qfullmsk; scalar_t__ sc_tx_timer; struct iwm_tx_ring* txq; } ;
struct iwm_cmd_header {int idx; int qid; } ;
struct iwm_rx_packet {struct iwm_cmd_header hdr; } ;
struct iwm_node {int /*<<< orphan*/  in_ni; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  IWM_DEBUG_XMIT ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,struct iwm_tx_data*,struct iwm_node*) ; 
 scalar_t__ IWM_TX_RING_LOMARK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ *,struct mbuf*,int) ; 
 int iwm_mvm_rx_tx_cmd_single (struct iwm_softc*,struct iwm_rx_packet*,struct iwm_node*) ; 
 int /*<<< orphan*/  iwm_start (struct iwm_softc*) ; 

__attribute__((used)) static void
iwm_mvm_rx_tx_cmd(struct iwm_softc *sc, struct iwm_rx_packet *pkt)
{
	struct iwm_cmd_header *cmd_hdr;
	struct iwm_tx_ring *ring;
	struct iwm_tx_data *txd;
	struct iwm_node *in;
	struct mbuf *m;
	int idx, qid, qmsk, status;

	cmd_hdr = &pkt->hdr;
	idx = cmd_hdr->idx;
	qid = cmd_hdr->qid;

	ring = &sc->txq[qid];
	txd = &ring->data[idx];
	in = txd->in;
	m = txd->m;

	KASSERT(txd->done == 0, ("txd not done"));
	KASSERT(txd->in != NULL, ("txd without node"));
	KASSERT(txd->m != NULL, ("txd without mbuf"));

	sc->sc_tx_timer = 0;

	status = iwm_mvm_rx_tx_cmd_single(sc, pkt, in);

	/* Unmap and free mbuf. */
	bus_dmamap_sync(ring->data_dmat, txd->map, BUS_DMASYNC_POSTWRITE);
	bus_dmamap_unload(ring->data_dmat, txd->map);

	IWM_DPRINTF(sc, IWM_DEBUG_XMIT,
	    "free txd %p, in %p\n", txd, txd->in);
	txd->done = 1;
	txd->m = NULL;
	txd->in = NULL;

	ieee80211_tx_complete(&in->in_ni, m, status);

	qmsk = 1 << qid;
	if (--ring->queued < IWM_TX_RING_LOMARK && (sc->qfullmsk & qmsk) != 0) {
		sc->qfullmsk &= ~qmsk;
		if (sc->qfullmsk == 0)
			iwm_start(sc);
	}
}