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
struct ieee80211_ratectl_tx_stats {int nframes; int nsuccess; int flags; int nretries; } ;
struct ieee80211_node {struct ieee80211_amrr_node* ni_rctls; } ;
struct ieee80211_amrr_node {int amn_txcnt; int amn_success; int amn_retrycnt; } ;

/* Variables and functions */
 int IEEE80211_RATECTL_TX_STATS_RETRIES ; 

__attribute__((used)) static void
amrr_tx_update_cb(void *arg, struct ieee80211_node *ni)
{
	struct ieee80211_ratectl_tx_stats *stats = arg;
	struct ieee80211_amrr_node *amn = ni->ni_rctls;
	int txcnt, success, retrycnt;

	if (!amn)
		return;

	txcnt = stats->nframes;
	success = stats->nsuccess;
	retrycnt = 0;
	if (stats->flags & IEEE80211_RATECTL_TX_STATS_RETRIES)
		retrycnt = stats->nretries;

	amn->amn_txcnt += txcnt;
	amn->amn_success += success;
	amn->amn_retrycnt += retrycnt;
}