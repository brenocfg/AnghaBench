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
struct ieee80211vap {scalar_t__* iv_ampdu_mintraffic; } ;
struct ieee80211_tx_ampdu {scalar_t__ txa_avgpps; scalar_t__ txa_attempts; int /*<<< orphan*/  txa_pkts; int /*<<< orphan*/  txa_tid; int /*<<< orphan*/  txa_nextrequest; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MSG_11N ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t TID_TO_WME_AC (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_addba_maxtries ; 
 scalar_t__ ieee80211_time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee80211_wme_acnames ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static int
ieee80211_ampdu_enable(struct ieee80211_node *ni,
	struct ieee80211_tx_ampdu *tap)
{
	struct ieee80211vap *vap = ni->ni_vap;

	if (tap->txa_avgpps <
	    vap->iv_ampdu_mintraffic[TID_TO_WME_AC(tap->txa_tid)])
		return 0;
	/* XXX check rssi? */
	if (tap->txa_attempts >= ieee80211_addba_maxtries &&
	    ieee80211_time_after(ticks, tap->txa_nextrequest)) {
		/*
		 * Don't retry too often; txa_nextrequest is set
		 * to the minimum interval we'll retry after
		 * ieee80211_addba_maxtries failed attempts are made.
		 */
		return 0;
	}
	IEEE80211_NOTE(vap, IEEE80211_MSG_11N, ni,
	    "enable AMPDU on tid %d (%s), avgpps %d pkts %d attempt %d",
	    tap->txa_tid, ieee80211_wme_acnames[TID_TO_WME_AC(tap->txa_tid)],
	    tap->txa_avgpps, tap->txa_pkts, tap->txa_attempts);
	return 1;
}