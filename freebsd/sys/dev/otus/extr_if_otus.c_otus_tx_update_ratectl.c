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
struct ieee80211_ratectl_tx_stats {int flags; scalar_t__ nretries; scalar_t__ nsuccess; scalar_t__ nframes; struct ieee80211_node* ni; } ;
struct otus_softc {struct ieee80211_ratectl_tx_stats sc_txs; } ;
struct otus_node {scalar_t__ tx_retries; scalar_t__ tx_err; scalar_t__ tx_done; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_vap; } ;

/* Variables and functions */
 int IEEE80211_RATECTL_TX_STATS_NODE ; 
 int IEEE80211_RATECTL_TX_STATS_RETRIES ; 
 struct otus_node* OTUS_NODE (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_ratectl_tx_update (int /*<<< orphan*/ ,struct ieee80211_ratectl_tx_stats*) ; 

__attribute__((used)) static void
otus_tx_update_ratectl(struct otus_softc *sc, struct ieee80211_node *ni)
{
	struct ieee80211_ratectl_tx_stats *txs = &sc->sc_txs;
	struct otus_node *on = OTUS_NODE(ni);

	txs->flags = IEEE80211_RATECTL_TX_STATS_NODE |
		     IEEE80211_RATECTL_TX_STATS_RETRIES;
	txs->ni = ni;
	txs->nframes = on->tx_done;
	txs->nsuccess = on->tx_done - on->tx_err;
	txs->nretries = on->tx_retries;

	ieee80211_ratectl_tx_update(ni->ni_vap, txs);
	on->tx_done = on->tx_err = on->tx_retries = 0;
}