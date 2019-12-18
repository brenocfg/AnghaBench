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
struct ieee80211_rx_ampdu {int rxa_flags; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int IEEE80211_AGGR_RUNNING ; 
 int IEEE80211_AGGR_WAITRX ; 
 int IEEE80211_AGGR_XCHGPEND ; 
 int /*<<< orphan*/  ampdu_rx_purge (struct ieee80211_rx_ampdu*) ; 

__attribute__((used)) static void
ampdu_rx_stop(struct ieee80211_node *ni, struct ieee80211_rx_ampdu *rap)
{

	ampdu_rx_purge(rap);
	rap->rxa_flags &= ~(IEEE80211_AGGR_RUNNING
	    | IEEE80211_AGGR_XCHGPEND
	    | IEEE80211_AGGR_WAITRX);
}