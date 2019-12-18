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
struct ieee80211vap {int dummy; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_mlhtimer; int /*<<< orphan*/  ni_mltimer; int /*<<< orphan*/  ni_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_NODE_QOS ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 

void
ieee80211_mesh_node_init(struct ieee80211vap *vap, struct ieee80211_node *ni)
{
	ni->ni_flags |= IEEE80211_NODE_QOS;
	callout_init(&ni->ni_mltimer, 1);
	callout_init(&ni->ni_mlhtimer, 1);
}