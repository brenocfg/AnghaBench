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
struct ieee80211vap {scalar_t__ iv_opmode; int /*<<< orphan*/  iv_sta_assoc; TYPE_1__* iv_auth; } ;
struct ieee80211com {int /*<<< orphan*/  ic_bsschan; int /*<<< orphan*/  ic_sta_assoc; } ;
struct ieee80211_node_table {int dummy; } ;
struct ieee80211_node {scalar_t__ ni_associd; struct ieee80211_node_table* ni_table; struct ieee80211vap* ni_vap; struct ieee80211com* ni_ic; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ia_node_leave ) (struct ieee80211_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AID_CLR (struct ieee80211vap*,scalar_t__) ; 
 scalar_t__ IEEE80211_IS_CHAN_ANYG (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_FULL (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_HT (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_VHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int IEEE80211_MSG_ASSOC ; 
 int IEEE80211_MSG_DEBUG ; 
 scalar_t__ IEEE80211_M_STA ; 
 int /*<<< orphan*/  IEEE80211_NODE_AID (struct ieee80211_node*) ; 
 int /*<<< orphan*/  IEEE80211_NODE_LOCK (struct ieee80211_node_table*) ; 
 int /*<<< orphan*/  IEEE80211_NODE_UNLOCK (struct ieee80211_node_table*) ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  ieee80211_free_node (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_ht_node_leave (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_node_leave_11g (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_sta_leave (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_vht_node_leave (struct ieee80211_node*) ; 
 int /*<<< orphan*/  node_reclaim (struct ieee80211_node_table*,struct ieee80211_node*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*) ; 

void
ieee80211_node_leave(struct ieee80211_node *ni)
{
	struct ieee80211com *ic = ni->ni_ic;
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_node_table *nt = ni->ni_table;

	IEEE80211_NOTE(vap, IEEE80211_MSG_ASSOC | IEEE80211_MSG_DEBUG, ni,
	    "station with aid %d leaves", IEEE80211_NODE_AID(ni));

	KASSERT(vap->iv_opmode != IEEE80211_M_STA,
		("unexpected operating mode %u", vap->iv_opmode));
	/*
	 * If node wasn't previously associated all
	 * we need to do is reclaim the reference.
	 */
	/* XXX ibss mode bypasses 11g and notification */
	if (ni->ni_associd == 0)
		goto done;
	/*
	 * Tell the authenticator the station is leaving.
	 * Note that we must do this before yanking the
	 * association id as the authenticator uses the
	 * associd to locate it's state block.
	 */
	if (vap->iv_auth->ia_node_leave != NULL)
		vap->iv_auth->ia_node_leave(ni);

	IEEE80211_LOCK(ic);
	IEEE80211_AID_CLR(vap, ni->ni_associd);
	vap->iv_sta_assoc--;
	ic->ic_sta_assoc--;

	if (IEEE80211_IS_CHAN_VHT(ic->ic_bsschan))
		ieee80211_vht_node_leave(ni);
	if (IEEE80211_IS_CHAN_HT(ic->ic_bsschan))
		ieee80211_ht_node_leave(ni);
	if (IEEE80211_IS_CHAN_ANYG(ic->ic_bsschan) &&
	    IEEE80211_IS_CHAN_FULL(ic->ic_bsschan))
		ieee80211_node_leave_11g(ni);
	IEEE80211_UNLOCK(ic);
	/*
	 * Cleanup station state.  In particular clear various
	 * state that might otherwise be reused if the node
	 * is reused before the reference count goes to zero
	 * (and memory is reclaimed).
	 */
	ieee80211_sta_leave(ni);
done:
	/*
	 * Remove the node from any table it's recorded in and
	 * drop the caller's reference.  Removal from the table
	 * is important to insure the node is not reprocessed
	 * for inactivity.
	 */
	if (nt != NULL) {
		IEEE80211_NODE_LOCK(nt);
		node_reclaim(nt, ni);
		IEEE80211_NODE_UNLOCK(nt);
	} else
		ieee80211_free_node(ni);
}