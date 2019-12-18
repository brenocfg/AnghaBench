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
struct ieee80211_node {int ni_flags; int ni_htcap; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int IEEE80211_FHT_SHORTGI20 ; 
 int IEEE80211_FHT_SHORTGI40 ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int IEEE80211_NODE_SGI20 ; 
 int IEEE80211_NODE_SGI40 ; 

__attribute__((used)) static __inline void
htcap_update_shortgi(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;

	ni->ni_flags &= ~(IEEE80211_NODE_SGI20|IEEE80211_NODE_SGI40);
	if ((ni->ni_htcap & IEEE80211_HTCAP_SHORTGI20) &&
	    (vap->iv_flags_ht & IEEE80211_FHT_SHORTGI20))
		ni->ni_flags |= IEEE80211_NODE_SGI20;
	if ((ni->ni_htcap & IEEE80211_HTCAP_SHORTGI40) &&
	    (vap->iv_flags_ht & IEEE80211_FHT_SHORTGI40))
		ni->ni_flags |= IEEE80211_NODE_SGI40;
}