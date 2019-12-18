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
struct ieee80211_tx_ampdu {int dummy; } ;
struct ieee80211_node {int dummy; } ;
struct ath_tid {int /*<<< orphan*/  tid; } ;
struct TYPE_6__ {int /*<<< orphan*/  ast_tx_aggr_fail; int /*<<< orphan*/  ast_tx_aggr_failall; } ;
struct ath_softc {TYPE_3__ sc_stats; } ;
struct ath_node {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bfs_nframes; int /*<<< orphan*/  bfs_pktlen; int /*<<< orphan*/  bfs_rc; } ;
struct TYPE_4__ {int /*<<< orphan*/  ds_txstat; } ;
struct ath_buf {struct ath_buf* bf_next; TYPE_2__ bf_state; TYPE_1__ bf_status; struct ieee80211_node* bf_node; } ;
typedef  int /*<<< orphan*/  ath_bufhead ;

/* Variables and functions */
 struct ath_node* ATH_NODE (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ATH_TID_INSERT_HEAD (struct ath_tid*,struct ath_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_TX_LOCK (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_TX_UNLOCK (struct ath_softc*) ; 
 struct ath_buf* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ath_buf*,int /*<<< orphan*/ ) ; 
 struct ath_buf* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ath_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_bufhead_s ; 
 int /*<<< orphan*/  ath_tx_default_comp (struct ath_softc*,struct ath_buf*,int /*<<< orphan*/ ) ; 
 struct ieee80211_tx_ampdu* ath_tx_get_tx_tid (struct ath_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath_tx_retry_subframe (struct ath_softc*,struct ath_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_tx_tid_bar_suspend (struct ath_softc*,struct ath_tid*) ; 
 int /*<<< orphan*/  ath_tx_tid_bar_tx (struct ath_softc*,struct ath_tid*) ; 
 scalar_t__ ath_tx_tid_bar_tx_ready (struct ath_softc*,struct ath_tid*) ; 
 int /*<<< orphan*/  ath_tx_tid_sched (struct ath_softc*,struct ath_tid*) ; 
 int /*<<< orphan*/  ath_tx_update_ratectrl (struct ath_softc*,struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_list ; 

__attribute__((used)) static void
ath_tx_comp_aggr_error(struct ath_softc *sc, struct ath_buf *bf_first,
    struct ath_tid *tid)
{
	struct ieee80211_node *ni = bf_first->bf_node;
	struct ath_node *an = ATH_NODE(ni);
	struct ath_buf *bf_next, *bf;
	ath_bufhead bf_q;
	int drops = 0;
	struct ieee80211_tx_ampdu *tap;
	ath_bufhead bf_cq;

	TAILQ_INIT(&bf_q);
	TAILQ_INIT(&bf_cq);

	/*
	 * Update rate control - all frames have failed.
	 *
	 * XXX use the length in the first frame in the series;
	 * XXX just so things are consistent for now.
	 */
	ath_tx_update_ratectrl(sc, ni, bf_first->bf_state.bfs_rc,
	    &bf_first->bf_status.ds_txstat,
	    bf_first->bf_state.bfs_pktlen,
	    bf_first->bf_state.bfs_nframes, bf_first->bf_state.bfs_nframes);

	ATH_TX_LOCK(sc);
	tap = ath_tx_get_tx_tid(an, tid->tid);
	sc->sc_stats.ast_tx_aggr_failall++;

	/* Retry all subframes */
	bf = bf_first;
	while (bf) {
		bf_next = bf->bf_next;
		bf->bf_next = NULL;	/* Remove it from the aggr list */
		sc->sc_stats.ast_tx_aggr_fail++;
		if (ath_tx_retry_subframe(sc, bf, &bf_q)) {
			drops++;
			bf->bf_next = NULL;
			TAILQ_INSERT_TAIL(&bf_cq, bf, bf_list);
		}
		bf = bf_next;
	}

	/* Prepend all frames to the beginning of the queue */
	while ((bf = TAILQ_LAST(&bf_q, ath_bufhead_s)) != NULL) {
		TAILQ_REMOVE(&bf_q, bf, bf_list);
		ATH_TID_INSERT_HEAD(tid, bf, bf_list);
	}

	/*
	 * Schedule the TID to be re-tried.
	 */
	ath_tx_tid_sched(sc, tid);

	/*
	 * send bar if we dropped any frames
	 *
	 * Keep the txq lock held for now, as we need to ensure
	 * that ni_txseqs[] is consistent (as it's being updated
	 * in the ifnet TX context or raw TX context.)
	 */
	if (drops) {
		/* Suspend the TX queue and get ready to send the BAR */
		ath_tx_tid_bar_suspend(sc, tid);
	}

	/*
	 * Send BAR if required
	 */
	if (ath_tx_tid_bar_tx_ready(sc, tid))
		ath_tx_tid_bar_tx(sc, tid);

	ATH_TX_UNLOCK(sc);

	/* Complete frames which errored out */
	while ((bf = TAILQ_FIRST(&bf_cq)) != NULL) {
		TAILQ_REMOVE(&bf_cq, bf, bf_list);
		ath_tx_default_comp(sc, bf, 0);
	}
}