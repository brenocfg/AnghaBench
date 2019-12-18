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
struct mlmeop {scalar_t__ op; int /*<<< orphan*/  reason; struct ieee80211vap* vap; } ;
struct ieee80211vap {int dummy; } ;
struct ieee80211_node {scalar_t__ ni_associd; int /*<<< orphan*/  ni_macaddr; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DEAUTH ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DISASSOC ; 
 scalar_t__ IEEE80211_MLME_DEAUTH ; 
 int /*<<< orphan*/  IEEE80211_SEND_MGMT (struct ieee80211_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_node_leave (struct ieee80211_node*) ; 
 int /*<<< orphan*/  mlmedebug (struct ieee80211vap*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
domlme(void *arg, struct ieee80211_node *ni)
{
	struct mlmeop *mop = arg;
	struct ieee80211vap *vap = ni->ni_vap;

	if (vap != mop->vap)
		return;
	/*
	 * NB: if ni_associd is zero then the node is already cleaned
	 * up and we don't need to do this (we're safely holding a
	 * reference but should otherwise not modify it's state).
	 */ 
	if (ni->ni_associd == 0)
		return;
	mlmedebug(vap, ni->ni_macaddr, mop->op, mop->reason);
	if (mop->op == IEEE80211_MLME_DEAUTH) {
		IEEE80211_SEND_MGMT(ni, IEEE80211_FC0_SUBTYPE_DEAUTH,
		    mop->reason);
	} else {
		IEEE80211_SEND_MGMT(ni, IEEE80211_FC0_SUBTYPE_DISASSOC,
		    mop->reason);
	}
	ieee80211_node_leave(ni);
}