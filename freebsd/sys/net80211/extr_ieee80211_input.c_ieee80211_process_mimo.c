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
struct ieee80211_rx_stats {int r_flags; int /*<<< orphan*/  c_chain; int /*<<< orphan*/ * c_nf_ext; int /*<<< orphan*/ * c_nf_ctl; int /*<<< orphan*/ * c_rssi_ext; int /*<<< orphan*/ * c_rssi_ctl; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_mimo_chains; int /*<<< orphan*/ * ni_mimo_noise_ext; int /*<<< orphan*/ * ni_mimo_noise_ctl; int /*<<< orphan*/ * ni_mimo_rssi_ext; int /*<<< orphan*/ * ni_mimo_rssi_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MAX_CHAINS ; 
 int /*<<< orphan*/  IEEE80211_RSSI_LPF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_R_C_CHAIN ; 
 int IEEE80211_R_C_NF ; 
 int IEEE80211_R_C_RSSI ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ieee80211_process_mimo(struct ieee80211_node *ni, struct ieee80211_rx_stats *rx)
{
	int i;

	/* Verify the required MIMO bits are set */
	if ((rx->r_flags & (IEEE80211_R_C_CHAIN | IEEE80211_R_C_NF | IEEE80211_R_C_RSSI)) !=
	    (IEEE80211_R_C_CHAIN | IEEE80211_R_C_NF | IEEE80211_R_C_RSSI))
		return;

	/* XXX This assumes the MIMO radios have both ctl and ext chains */
	for (i = 0; i < MIN(rx->c_chain, IEEE80211_MAX_CHAINS); i++) {
		IEEE80211_RSSI_LPF(ni->ni_mimo_rssi_ctl[i], rx->c_rssi_ctl[i]);
		IEEE80211_RSSI_LPF(ni->ni_mimo_rssi_ext[i], rx->c_rssi_ext[i]);
	}

	/* XXX This also assumes the MIMO radios have both ctl and ext chains */
	for(i = 0; i < MIN(rx->c_chain, IEEE80211_MAX_CHAINS); i++) {
		ni->ni_mimo_noise_ctl[i] = rx->c_nf_ctl[i];
		ni->ni_mimo_noise_ext[i] = rx->c_nf_ext[i];
	}
	ni->ni_mimo_chains = rx->c_chain;
}