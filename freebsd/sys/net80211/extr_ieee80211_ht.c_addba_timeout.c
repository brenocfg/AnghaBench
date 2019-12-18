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
struct ieee80211com {int /*<<< orphan*/  (* ic_addba_response_timeout ) (struct ieee80211_node*,struct ieee80211_tx_ampdu*) ;} ;
struct ieee80211_tx_ampdu {int /*<<< orphan*/  txa_attempts; int /*<<< orphan*/  txa_flags; struct ieee80211_node* txa_ni; } ;
struct ieee80211_node {struct ieee80211com* ni_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AGGR_XCHGPEND ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,struct ieee80211_tx_ampdu*) ; 

__attribute__((used)) static void
addba_timeout(void *arg)
{
	struct ieee80211_tx_ampdu *tap = arg;
	struct ieee80211_node *ni = tap->txa_ni;
	struct ieee80211com *ic = ni->ni_ic;

	/* XXX ? */
	tap->txa_flags &= ~IEEE80211_AGGR_XCHGPEND;
	tap->txa_attempts++;
	ic->ic_addba_response_timeout(ni, tap);
}