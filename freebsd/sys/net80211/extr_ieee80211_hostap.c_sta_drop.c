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
struct ieee80211_node {scalar_t__ ni_associd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_node_leave (struct ieee80211_node*) ; 

__attribute__((used)) static void
sta_drop(void *arg, struct ieee80211_node *ni)
{

	if (ni->ni_associd != 0)
		ieee80211_node_leave(ni);
}