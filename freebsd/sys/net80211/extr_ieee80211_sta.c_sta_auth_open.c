#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ is_rx_authfail_code; int /*<<< orphan*/  is_rx_auth_fail; int /*<<< orphan*/  is_rx_bad_auth; } ;
struct ieee80211vap {scalar_t__ iv_state; TYPE_1__ iv_stats; } ;
struct ieee80211_node {scalar_t__ ni_authmode; int /*<<< orphan*/  ni_macaddr; struct ieee80211vap* ni_vap; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_AUTH_OPEN_RESPONSE ; 
 scalar_t__ IEEE80211_AUTH_SHARED ; 
 int /*<<< orphan*/  IEEE80211_DISCARD_MAC (struct ieee80211vap*,int,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int IEEE80211_MSG_AUTH ; 
 int IEEE80211_MSG_DEBUG ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int,struct ieee80211_node*,char*,scalar_t__) ; 
 int /*<<< orphan*/  IEEE80211_SCAN_FAIL_STATUS ; 
 int /*<<< orphan*/  IEEE80211_S_ASSOC ; 
 scalar_t__ IEEE80211_S_AUTH ; 
 int /*<<< orphan*/  IEEE80211_S_SCAN ; 
 int /*<<< orphan*/  ieee80211_new_state (struct ieee80211vap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sta_auth_open(struct ieee80211_node *ni, struct ieee80211_frame *wh,
    int rssi, int nf, uint16_t seq, uint16_t status)
{
	struct ieee80211vap *vap = ni->ni_vap;

	if (ni->ni_authmode == IEEE80211_AUTH_SHARED) {
		IEEE80211_DISCARD_MAC(vap, IEEE80211_MSG_AUTH,
		    ni->ni_macaddr, "open auth",
		    "bad sta auth mode %u", ni->ni_authmode);
		vap->iv_stats.is_rx_bad_auth++;	/* XXX */
		return;
	}
	if (vap->iv_state != IEEE80211_S_AUTH ||
	    seq != IEEE80211_AUTH_OPEN_RESPONSE) {
		vap->iv_stats.is_rx_bad_auth++;
		return;
	}
	if (status != 0) {
		IEEE80211_NOTE(vap, IEEE80211_MSG_DEBUG | IEEE80211_MSG_AUTH,
		    ni, "open auth failed (reason %d)", status);
		vap->iv_stats.is_rx_auth_fail++;
		vap->iv_stats.is_rx_authfail_code = status;
		ieee80211_new_state(vap, IEEE80211_S_SCAN,
		    IEEE80211_SCAN_FAIL_STATUS);
	} else
		ieee80211_new_state(vap, IEEE80211_S_ASSOC, 0);
}