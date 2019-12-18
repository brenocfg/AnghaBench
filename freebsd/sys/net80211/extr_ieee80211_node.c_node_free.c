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
struct ieee80211com {int /*<<< orphan*/  (* ic_node_cleanup ) (struct ieee80211_node*) ;} ;
struct ieee80211_node {int /*<<< orphan*/  ni_psq; int /*<<< orphan*/  ni_ies; struct ieee80211com* ni_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (struct ieee80211_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_80211_NODE ; 
 int /*<<< orphan*/  ieee80211_ies_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_psq_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ratectl_node_deinit (struct ieee80211_node*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*) ; 

__attribute__((used)) static void
node_free(struct ieee80211_node *ni)
{
	struct ieee80211com *ic = ni->ni_ic;

	ieee80211_ratectl_node_deinit(ni);
	ic->ic_node_cleanup(ni);
	ieee80211_ies_cleanup(&ni->ni_ies);
	ieee80211_psq_cleanup(&ni->ni_psq);
	IEEE80211_FREE(ni, M_80211_NODE);
}