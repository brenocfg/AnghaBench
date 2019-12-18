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
struct ieee80211_tx_ampdu {int txa_flags; int /*<<< orphan*/  txa_timer; } ;

/* Variables and functions */
 int IEEE80211_AGGR_XCHGPEND ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
addba_stop_timeout(struct ieee80211_tx_ampdu *tap)
{
	/* XXX use CALLOUT_PENDING instead? */
	if (tap->txa_flags & IEEE80211_AGGR_XCHGPEND) {
		callout_stop(&tap->txa_timer);
		tap->txa_flags &= ~IEEE80211_AGGR_XCHGPEND;
	}
}