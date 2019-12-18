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
struct ieee80211vap {int iv_flags_ht; } ;
struct ieee80211_node {int ni_htcap; int /*<<< orphan*/  ni_flags; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int IEEE80211_FHT_LDPC_TX ; 
 int IEEE80211_HTCAP_LDPC ; 
 int /*<<< orphan*/  IEEE80211_NODE_LDPC ; 

__attribute__((used)) static __inline void
htcap_update_ldpc(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;

	if ((ni->ni_htcap & IEEE80211_HTCAP_LDPC) &&
	    (vap->iv_flags_ht & IEEE80211_FHT_LDPC_TX))
		ni->ni_flags |= IEEE80211_NODE_LDPC;
}