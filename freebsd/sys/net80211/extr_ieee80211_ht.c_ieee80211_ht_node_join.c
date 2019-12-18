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
struct ieee80211com {int /*<<< orphan*/  ic_ht40_sta_assoc; int /*<<< orphan*/  ic_ht_sta_assoc; } ;
struct ieee80211_node {int ni_flags; int ni_chw; struct ieee80211com* ni_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LOCK_ASSERT (struct ieee80211com*) ; 
 int IEEE80211_NODE_HT ; 
 int /*<<< orphan*/  htinfo_update (struct ieee80211com*) ; 

void
ieee80211_ht_node_join(struct ieee80211_node *ni)
{
	struct ieee80211com *ic = ni->ni_ic;

	IEEE80211_LOCK_ASSERT(ic);

	if (ni->ni_flags & IEEE80211_NODE_HT) {
		ic->ic_ht_sta_assoc++;
		if (ni->ni_chw == 40)
			ic->ic_ht40_sta_assoc++;
	}
	htinfo_update(ic);
}