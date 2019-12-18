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

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ACTION_BA_ADDBA_REQUEST ; 
 int /*<<< orphan*/  IEEE80211_ACTION_BA_ADDBA_RESPONSE ; 
 int /*<<< orphan*/  IEEE80211_ACTION_BA_DELBA ; 
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_BA ; 
 int /*<<< orphan*/  IEEE80211_ACTION_CAT_HT ; 
 int /*<<< orphan*/  IEEE80211_ACTION_HT_MIMOPWRSAVE ; 
 int /*<<< orphan*/  IEEE80211_ACTION_HT_TXCHWIDTH ; 
 int /*<<< orphan*/  ht_recv_action_ba_addba_request ; 
 int /*<<< orphan*/  ht_recv_action_ba_addba_response ; 
 int /*<<< orphan*/  ht_recv_action_ba_delba ; 
 int /*<<< orphan*/  ht_recv_action_ht_mimopwrsave ; 
 int /*<<< orphan*/  ht_recv_action_ht_txchwidth ; 
 int /*<<< orphan*/  ht_send_action_ba_addba ; 
 int /*<<< orphan*/  ht_send_action_ba_delba ; 
 int /*<<< orphan*/  ht_send_action_ht_txchwidth ; 
 void* ieee80211_addba_backoff ; 
 void* ieee80211_addba_timeout ; 
 void* ieee80211_ampdu_age ; 
 void* ieee80211_bar_timeout ; 
 int /*<<< orphan*/  ieee80211_recv_action_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_action_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* msecs_to_ticks (int) ; 

__attribute__((used)) static void
ieee80211_ht_init(void)
{
	/*
	 * Setup HT parameters that depends on the clock frequency.
	 */
	ieee80211_ampdu_age = msecs_to_ticks(500);
	ieee80211_addba_timeout = msecs_to_ticks(250);
	ieee80211_addba_backoff = msecs_to_ticks(10*1000);
	ieee80211_bar_timeout = msecs_to_ticks(250);
	/*
	 * Register action frame handlers.
	 */
	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_BA, 
	    IEEE80211_ACTION_BA_ADDBA_REQUEST, ht_recv_action_ba_addba_request);
	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_BA, 
	    IEEE80211_ACTION_BA_ADDBA_RESPONSE, ht_recv_action_ba_addba_response);
	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_BA, 
	    IEEE80211_ACTION_BA_DELBA, ht_recv_action_ba_delba);
	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_HT, 
	    IEEE80211_ACTION_HT_MIMOPWRSAVE, ht_recv_action_ht_mimopwrsave);
	ieee80211_recv_action_register(IEEE80211_ACTION_CAT_HT, 
	    IEEE80211_ACTION_HT_TXCHWIDTH, ht_recv_action_ht_txchwidth);

	ieee80211_send_action_register(IEEE80211_ACTION_CAT_BA, 
	    IEEE80211_ACTION_BA_ADDBA_REQUEST, ht_send_action_ba_addba);
	ieee80211_send_action_register(IEEE80211_ACTION_CAT_BA, 
	    IEEE80211_ACTION_BA_ADDBA_RESPONSE, ht_send_action_ba_addba);
	ieee80211_send_action_register(IEEE80211_ACTION_CAT_BA, 
	    IEEE80211_ACTION_BA_DELBA, ht_send_action_ba_delba);
	ieee80211_send_action_register(IEEE80211_ACTION_CAT_HT, 
	    IEEE80211_ACTION_HT_TXCHWIDTH, ht_send_action_ht_txchwidth);
}