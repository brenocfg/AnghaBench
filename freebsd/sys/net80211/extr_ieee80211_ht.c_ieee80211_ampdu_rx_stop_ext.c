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
struct ieee80211_rx_ampdu {int dummy; } ;
struct ieee80211_node {struct ieee80211_rx_ampdu* ni_rx_ampdu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ampdu_rx_stop (struct ieee80211_node*,struct ieee80211_rx_ampdu*) ; 

void
ieee80211_ampdu_rx_stop_ext(struct ieee80211_node *ni, int tid)
{
	struct ieee80211_rx_ampdu *rap;

	/* XXX TODO: sanity check tid, seq, baw */
	rap = &ni->ni_rx_ampdu[tid];
	ampdu_rx_stop(ni, rap);
}