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
struct mbuf {int dummy; } ;
struct ieee80211com {int dummy; } ;
struct ieee80211_rx_stats {int r_flags; int c_nf; int c_rssi; } ;

/* Variables and functions */
 int IEEE80211_R_NF ; 
 int IEEE80211_R_RSSI ; 
 int /*<<< orphan*/  ieee80211_add_rx_params (struct mbuf*,struct ieee80211_rx_stats*) ; 
 int ieee80211_input_mimo_all (struct ieee80211com*,struct mbuf*) ; 

int
ieee80211_input_all(struct ieee80211com *ic, struct mbuf *m, int rssi, int nf)
{
	struct ieee80211_rx_stats rx;

	rx.r_flags = IEEE80211_R_NF | IEEE80211_R_RSSI;
	rx.c_nf = nf;
	rx.c_rssi = rssi;

	if (!ieee80211_add_rx_params(m, &rx))
		return (-1);

	return ieee80211_input_mimo_all(ic, m);
}