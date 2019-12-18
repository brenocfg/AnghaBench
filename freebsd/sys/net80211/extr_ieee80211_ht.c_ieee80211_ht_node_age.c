#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  is_ampdu_rx_age; } ;
struct ieee80211vap {TYPE_1__ iv_stats; } ;
struct ieee80211_rx_ampdu {int rxa_flags; scalar_t__ rxa_qframes; scalar_t__ rxa_age; } ;
struct ieee80211_node {int ni_flags; struct ieee80211_rx_ampdu* ni_rx_ampdu; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int IEEE80211_AGGR_XCHGPEND ; 
 int IEEE80211_NODE_HT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t WME_NUM_TID ; 
 int /*<<< orphan*/  ampdu_rx_flush (struct ieee80211_node*,struct ieee80211_rx_ampdu*) ; 
 scalar_t__ ieee80211_ampdu_age ; 
 scalar_t__ ticks ; 

void
ieee80211_ht_node_age(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	uint8_t tid;

	KASSERT(ni->ni_flags & IEEE80211_NODE_HT, ("not an HT sta"));

	for (tid = 0; tid < WME_NUM_TID; tid++) {
		struct ieee80211_rx_ampdu *rap;

		rap = &ni->ni_rx_ampdu[tid];
		if ((rap->rxa_flags & IEEE80211_AGGR_XCHGPEND) == 0)
			continue;
		if (rap->rxa_qframes == 0)
			continue;
		/* 
		 * Check for frames sitting too long in the reorder queue.
		 * See above for more details on what's happening here.
		 */
		/* XXX honor batimeout? */
		if (ticks - rap->rxa_age > ieee80211_ampdu_age) {
			/*
			 * Too long since we received the first
			 * frame; flush the reorder buffer.
			 */
			vap->iv_stats.is_ampdu_rx_age += rap->rxa_qframes;
			ampdu_rx_flush(ni, rap);
		}
	}
}