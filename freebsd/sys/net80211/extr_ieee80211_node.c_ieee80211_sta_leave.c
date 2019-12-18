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
struct ieee80211_node {struct ieee80211com* ni_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_notify_node_leave (struct ieee80211_node*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*) ; 

void
ieee80211_sta_leave(struct ieee80211_node *ni)
{
	struct ieee80211com *ic = ni->ni_ic;

	ic->ic_node_cleanup(ni);
	ieee80211_notify_node_leave(ni);
}