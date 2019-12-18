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
struct ieee80211_tx_ampdu {int txa_flags; scalar_t__ txa_attempts; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int IEEE80211_AGGR_RUNNING ; 
 int /*<<< orphan*/  addba_stop_timeout (struct ieee80211_tx_ampdu*) ; 

__attribute__((used)) static void
ieee80211_addba_stop(struct ieee80211_node *ni, struct ieee80211_tx_ampdu *tap)
{
	/* XXX locking */
	addba_stop_timeout(tap);
	if (tap->txa_flags & IEEE80211_AGGR_RUNNING) {
		/* XXX clear aggregation queue */
		tap->txa_flags &= ~IEEE80211_AGGR_RUNNING;
	}
	tap->txa_attempts = 0;
}