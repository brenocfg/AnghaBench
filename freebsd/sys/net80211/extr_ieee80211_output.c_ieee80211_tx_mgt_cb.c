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
struct ieee80211vap {int iv_state; int /*<<< orphan*/  iv_mgtsend; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;
typedef  enum ieee80211_state { ____Placeholder_ieee80211_state } ieee80211_state ;

/* Variables and functions */
 int IEEE80211_TRANS_WAIT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ieee80211vap*) ; 
 int hz ; 
 int /*<<< orphan*/  ieee80211_tx_mgt_timeout ; 

__attribute__((used)) static void
ieee80211_tx_mgt_cb(struct ieee80211_node *ni, void *arg, int status)
{
	struct ieee80211vap *vap = ni->ni_vap;
	enum ieee80211_state ostate = (enum ieee80211_state) arg;

	/*
	 * Frame transmit completed; arrange timer callback.  If
	 * transmit was successfully we wait for response.  Otherwise
	 * we arrange an immediate callback instead of doing the
	 * callback directly since we don't know what state the driver
	 * is in (e.g. what locks it is holding).  This work should
	 * not be too time-critical and not happen too often so the
	 * added overhead is acceptable.
	 *
	 * XXX what happens if !acked but response shows up before callback?
	 */
	if (vap->iv_state == ostate) {
		callout_reset(&vap->iv_mgtsend,
			status == 0 ? IEEE80211_TRANS_WAIT*hz : 0,
			ieee80211_tx_mgt_timeout, vap);
	}
}