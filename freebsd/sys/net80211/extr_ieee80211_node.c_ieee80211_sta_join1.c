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
struct ieee80211vap {scalar_t__ iv_state; scalar_t__ iv_opmode; struct ieee80211_node* iv_bss; } ;
struct ieee80211com {int dummy; } ;
struct ieee80211_node_table {int dummy; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_chan; int /*<<< orphan*/  ni_rates; struct ieee80211_node_table* ni_table; int /*<<< orphan*/  ni_macaddr; struct ieee80211com* ni_ic; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_FC0_SUBTYPE_DEAUTH ; 
 int IEEE80211_F_DODEL ; 
 int IEEE80211_F_JOIN ; 
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_NODE_LOCK (struct ieee80211_node_table*) ; 
 int /*<<< orphan*/  IEEE80211_NODE_UNLOCK (struct ieee80211_node_table*) ; 
 scalar_t__ IEEE80211_S_ASSOC ; 
 scalar_t__ IEEE80211_S_AUTH ; 
 scalar_t__ IEEE80211_S_RUN ; 
 int /*<<< orphan*/  copy_bss (struct ieee80211_node*,struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_fix_rate (struct ieee80211_node*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_new_state (struct ieee80211vap*,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee80211_node_decref (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_reset_erp (struct ieee80211com*) ; 
 int /*<<< orphan*/  ieee80211_setcurchan (struct ieee80211com*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wme_initparams (struct ieee80211vap*) ; 
 int /*<<< orphan*/  node_reclaim (struct ieee80211_node_table*,struct ieee80211_node*) ; 

__attribute__((used)) static int
ieee80211_sta_join1(struct ieee80211_node *selbs)
{
	struct ieee80211vap *vap = selbs->ni_vap;
	struct ieee80211com *ic = selbs->ni_ic;
	struct ieee80211_node *obss;
	int canreassoc;

	/*
	 * Committed to selbs, setup state.
	 */
	obss = vap->iv_bss;
	/*
	 * Check if old+new node have the same address in which
	 * case we can reassociate when operating in sta mode.
	 */
	canreassoc = (obss != NULL &&
		vap->iv_state == IEEE80211_S_RUN &&
		IEEE80211_ADDR_EQ(obss->ni_macaddr, selbs->ni_macaddr));
	vap->iv_bss = selbs;		/* NB: caller assumed to bump refcnt */
	if (obss != NULL) {
		struct ieee80211_node_table *nt = obss->ni_table;

		copy_bss(selbs, obss);
		ieee80211_node_decref(obss);	/* iv_bss reference */

		IEEE80211_NODE_LOCK(nt);
		node_reclaim(nt, obss);		/* station table reference */
		IEEE80211_NODE_UNLOCK(nt);

		obss = NULL;		/* NB: guard against later use */
	}

	/*
	 * Delete unusable rates; we've already checked
	 * that the negotiated rate set is acceptable.
	 */
	ieee80211_fix_rate(vap->iv_bss, &vap->iv_bss->ni_rates,
		IEEE80211_F_DODEL | IEEE80211_F_JOIN);

	ieee80211_setcurchan(ic, selbs->ni_chan);
	/*
	 * Set the erp state (mostly the slot time) to deal with
	 * the auto-select case; this should be redundant if the
	 * mode is locked.
	 */
	ieee80211_reset_erp(ic);
	ieee80211_wme_initparams(vap);

	if (vap->iv_opmode == IEEE80211_M_STA) {
		if (canreassoc) {
			/* Reassociate */
			ieee80211_new_state(vap, IEEE80211_S_ASSOC, 1);
		} else {
			/*
			 * Act as if we received a DEAUTH frame in case we
			 * are invoked from the RUN state.  This will cause
			 * us to try to re-authenticate if we are operating
			 * as a station.
			 */
			ieee80211_new_state(vap, IEEE80211_S_AUTH,
				IEEE80211_FC0_SUBTYPE_DEAUTH);
		}
	} else
		ieee80211_new_state(vap, IEEE80211_S_RUN, -1);
	return 1;
}