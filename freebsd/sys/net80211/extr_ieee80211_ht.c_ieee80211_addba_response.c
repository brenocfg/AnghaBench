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
struct ieee80211_tx_ampdu {int /*<<< orphan*/  txa_flags; scalar_t__ txa_attempts; int /*<<< orphan*/  txa_wnd; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AGGR_BAWMAX ; 
 int /*<<< orphan*/  IEEE80211_AGGR_NAK ; 
 int /*<<< orphan*/  IEEE80211_AGGR_RUNNING ; 
 int /*<<< orphan*/  IEEE80211_BAPS_BUFSIZ ; 
 int /*<<< orphan*/  IEEE80211_BAPS_TID ; 
 int IEEE80211_STATUS_SUCCESS ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addba_stop_timeout (struct ieee80211_tx_ampdu*) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ieee80211_addba_response(struct ieee80211_node *ni,
	struct ieee80211_tx_ampdu *tap,
	int status, int baparamset, int batimeout)
{
	int bufsiz, tid;

	/* XXX locking */
	addba_stop_timeout(tap);
	if (status == IEEE80211_STATUS_SUCCESS) {
		bufsiz = MS(baparamset, IEEE80211_BAPS_BUFSIZ);
		/* XXX override our request? */
		tap->txa_wnd = (bufsiz == 0) ?
		    IEEE80211_AGGR_BAWMAX : min(bufsiz, IEEE80211_AGGR_BAWMAX);
		/* XXX AC/TID */
		tid = MS(baparamset, IEEE80211_BAPS_TID);
		tap->txa_flags |= IEEE80211_AGGR_RUNNING;
		tap->txa_attempts = 0;
	} else {
		/* mark tid so we don't try again */
		tap->txa_flags |= IEEE80211_AGGR_NAK;
	}
	return 1;
}