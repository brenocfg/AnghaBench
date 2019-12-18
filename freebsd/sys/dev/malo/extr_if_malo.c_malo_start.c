#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct malo_txq {int /*<<< orphan*/  free; } ;
struct malo_txbuf {int /*<<< orphan*/ * bf_node; int /*<<< orphan*/ * bf_m; } ;
struct TYPE_5__ {int /*<<< orphan*/  mst_tx_qstop; } ;
struct malo_softc {int /*<<< orphan*/  malo_mh; TYPE_2__ malo_stats; int /*<<< orphan*/  malo_snd; scalar_t__ malo_invalid; int /*<<< orphan*/  malo_running; struct malo_txq* malo_txq; } ;
struct ieee80211_node {TYPE_3__* ni_vap; } ;
struct TYPE_6__ {int /*<<< orphan*/  iv_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  MALO_LOCK_ASSERT (struct malo_softc*) ; 
 int /*<<< orphan*/  MALO_TXQ_LOCK (struct malo_txq*) ; 
 int /*<<< orphan*/  MALO_TXQ_UNLOCK (struct malo_txq*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct malo_txbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_list ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct malo_txbuf* malo_getbuf (struct malo_softc*,struct malo_txq*) ; 
 int /*<<< orphan*/  malo_hal_txstart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malo_tx_start (struct malo_softc*,struct ieee80211_node*,struct malo_txbuf*,struct mbuf*) ; 
 int malo_txcoalesce ; 
 struct mbuf* mbufq_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbufq_prepend (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static void
malo_start(struct malo_softc *sc)
{
	struct ieee80211_node *ni;
	struct malo_txq *txq = &sc->malo_txq[0];
	struct malo_txbuf *bf = NULL;
	struct mbuf *m;
	int nqueued = 0;

	MALO_LOCK_ASSERT(sc);

	if (!sc->malo_running || sc->malo_invalid)
		return;

	while ((m = mbufq_dequeue(&sc->malo_snd)) != NULL) {
		ni = (struct ieee80211_node *) m->m_pkthdr.rcvif;
		bf = malo_getbuf(sc, txq);
		if (bf == NULL) {
			mbufq_prepend(&sc->malo_snd, m);
			sc->malo_stats.mst_tx_qstop++;
			break;
		}
		/*
		 * Pass the frame to the h/w for transmission.
		 */
		if (malo_tx_start(sc, ni, bf, m)) {
			if_inc_counter(ni->ni_vap->iv_ifp,
			    IFCOUNTER_OERRORS, 1);
			if (bf != NULL) {
				bf->bf_m = NULL;
				bf->bf_node = NULL;
				MALO_TXQ_LOCK(txq);
				STAILQ_INSERT_HEAD(&txq->free, bf, bf_list);
				MALO_TXQ_UNLOCK(txq);
			}
			ieee80211_free_node(ni);
			continue;
		}
		nqueued++;

		if (nqueued >= malo_txcoalesce) {
			/*
			 * Poke the firmware to process queued frames;
			 * see below about (lack of) locking.
			 */
			nqueued = 0;
			malo_hal_txstart(sc->malo_mh, 0/*XXX*/);
		}
	}

	if (nqueued) {
		/*
		 * NB: We don't need to lock against tx done because
		 * this just prods the firmware to check the transmit
		 * descriptors.  The firmware will also start fetching
		 * descriptors by itself if it notices new ones are
		 * present when it goes to deliver a tx done interrupt
		 * to the host. So if we race with tx done processing
		 * it's ok.  Delivering the kick here rather than in
		 * malo_tx_start is an optimization to avoid poking the
		 * firmware for each packet.
		 *
		 * NB: the queue id isn't used so 0 is ok.
		 */
		malo_hal_txstart(sc->malo_mh, 0/*XXX*/);
	}
}