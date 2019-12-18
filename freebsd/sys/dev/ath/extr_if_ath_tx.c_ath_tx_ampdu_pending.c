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
struct ieee80211_tx_ampdu {int txa_flags; } ;
struct ath_softc {int dummy; } ;
struct ath_node {int dummy; } ;

/* Variables and functions */
 int IEEE80211_AGGR_XCHGPEND ; 
 int IEEE80211_NONQOS_TID ; 
 struct ieee80211_tx_ampdu* ath_tx_get_tx_tid (struct ath_node*,int) ; 

__attribute__((used)) static int
ath_tx_ampdu_pending(struct ath_softc *sc, struct ath_node *an, int tid)
{
	struct ieee80211_tx_ampdu *tap;

	if (tid == IEEE80211_NONQOS_TID)
		return 0;

	tap = ath_tx_get_tx_tid(an, tid);
	if (tap == NULL)
		return 0;	/* Not valid; default to not pending */

	return !! (tap->txa_flags & IEEE80211_AGGR_XCHGPEND);
}