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
struct ieee80211com {int /*<<< orphan*/  ic_curhtprotmode; int /*<<< orphan*/  ic_htprotmode; int /*<<< orphan*/  ic_ampdu_rx_stop; int /*<<< orphan*/  ic_ampdu_rx_start; int /*<<< orphan*/  ic_bar_response; int /*<<< orphan*/  ic_addba_stop; int /*<<< orphan*/  ic_addba_response_timeout; int /*<<< orphan*/  ic_addba_response; int /*<<< orphan*/  ic_addba_request; int /*<<< orphan*/  ic_ampdu_enable; int /*<<< orphan*/  ic_send_action; int /*<<< orphan*/  ic_recv_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_HTINFO_OPMODE_PURE ; 
 int /*<<< orphan*/  IEEE80211_PROT_RTSCTS ; 
 int /*<<< orphan*/  ampdu_rx_start ; 
 int /*<<< orphan*/  ampdu_rx_stop ; 
 int /*<<< orphan*/  ieee80211_addba_request ; 
 int /*<<< orphan*/  ieee80211_addba_response ; 
 int /*<<< orphan*/  ieee80211_addba_stop ; 
 int /*<<< orphan*/  ieee80211_ampdu_enable ; 
 int /*<<< orphan*/  ieee80211_bar_response ; 
 int /*<<< orphan*/  ieee80211_recv_action ; 
 int /*<<< orphan*/  ieee80211_send_action ; 
 int /*<<< orphan*/  null_addba_response_timeout ; 

void
ieee80211_ht_attach(struct ieee80211com *ic)
{
	/* setup default aggregation policy */
	ic->ic_recv_action = ieee80211_recv_action;
	ic->ic_send_action = ieee80211_send_action;
	ic->ic_ampdu_enable = ieee80211_ampdu_enable;
	ic->ic_addba_request = ieee80211_addba_request;
	ic->ic_addba_response = ieee80211_addba_response;
	ic->ic_addba_response_timeout = null_addba_response_timeout;
	ic->ic_addba_stop = ieee80211_addba_stop;
	ic->ic_bar_response = ieee80211_bar_response;
	ic->ic_ampdu_rx_start = ampdu_rx_start;
	ic->ic_ampdu_rx_stop = ampdu_rx_stop;

	ic->ic_htprotmode = IEEE80211_PROT_RTSCTS;
	ic->ic_curhtprotmode = IEEE80211_HTINFO_OPMODE_PURE;
}