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
struct ieee80211_tx_ampdu {int /*<<< orphan*/  txa_lastsample; int /*<<< orphan*/  txa_flags; int /*<<< orphan*/  txa_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AGGR_SETUP ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static void
ampdu_tx_setup(struct ieee80211_tx_ampdu *tap)
{
	callout_init(&tap->txa_timer, 1);
	tap->txa_flags |= IEEE80211_AGGR_SETUP;
	tap->txa_lastsample = ticks;
}