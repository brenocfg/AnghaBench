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
struct ieee80211vap {int /*<<< orphan*/  iv_myaddr; struct ieee80211_node* iv_bss; struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_bintval; int /*<<< orphan*/  ic_sta; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_bssid; int /*<<< orphan*/  ni_intval; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  copy_bss (struct ieee80211_node*,struct ieee80211_node*) ; 
 struct ieee80211_node* ieee80211_alloc_node (int /*<<< orphan*/ *,struct ieee80211vap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_node_table_reset (int /*<<< orphan*/ *,struct ieee80211vap*) ; 
 struct ieee80211_node* ieee80211_ref_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_reset_erp (struct ieee80211com*) ; 

void
ieee80211_reset_bss(struct ieee80211vap *vap)
{
	struct ieee80211com *ic = vap->iv_ic;
	struct ieee80211_node *ni, *obss;

	ieee80211_node_table_reset(&ic->ic_sta, vap);
	/* XXX multi-bss: wrong */
	ieee80211_reset_erp(ic);

	ni = ieee80211_alloc_node(&ic->ic_sta, vap, vap->iv_myaddr);
	KASSERT(ni != NULL, ("unable to setup initial BSS node"));
	obss = vap->iv_bss;
	vap->iv_bss = ieee80211_ref_node(ni);
	if (obss != NULL) {
		copy_bss(ni, obss);
		ni->ni_intval = ic->ic_bintval;
		ieee80211_free_node(obss);
	} else
		IEEE80211_ADDR_COPY(ni->ni_bssid, vap->iv_myaddr);
}