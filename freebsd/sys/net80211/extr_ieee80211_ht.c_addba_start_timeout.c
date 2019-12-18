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
struct ieee80211_tx_ampdu {scalar_t__ txa_nextrequest; int /*<<< orphan*/  txa_flags; int /*<<< orphan*/  txa_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AGGR_XCHGPEND ; 
 int /*<<< orphan*/  addba_timeout ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct ieee80211_tx_ampdu*) ; 
 scalar_t__ ieee80211_addba_timeout ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
addba_start_timeout(struct ieee80211_tx_ampdu *tap)
{
	/* XXX use CALLOUT_PENDING instead? */
	callout_reset(&tap->txa_timer, ieee80211_addba_timeout,
	    addba_timeout, tap);
	tap->txa_flags |= IEEE80211_AGGR_XCHGPEND;
	tap->txa_nextrequest = ticks + ieee80211_addba_timeout;
}