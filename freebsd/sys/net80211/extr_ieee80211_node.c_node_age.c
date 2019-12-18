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
struct ieee80211vap {int /*<<< orphan*/  (* iv_set_tim ) (struct ieee80211_node*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {scalar_t__ psq_len; } ;
struct ieee80211_node {scalar_t__ ni_associd; int ni_flags; TYPE_1__ ni_psq; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int IEEE80211_NODE_HT ; 
 int /*<<< orphan*/  ieee80211_ht_node_age (struct ieee80211_node*) ; 
 scalar_t__ ieee80211_node_psq_age (struct ieee80211_node*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
node_age(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;

	/*
	 * Age frames on the power save queue.
	 */
	if (ieee80211_node_psq_age(ni) != 0 &&
	    ni->ni_psq.psq_len == 0 && vap->iv_set_tim != NULL)
		vap->iv_set_tim(ni, 0);
	/*
	 * Age out HT resources (e.g. frames on the
	 * A-MPDU reorder queues).
	 */
	if (ni->ni_associd != 0 && (ni->ni_flags & IEEE80211_NODE_HT))
		ieee80211_ht_node_age(ni);
}