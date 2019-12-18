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
struct TYPE_2__ {scalar_t__ rs_nrates; } ;
struct ieee80211_rssadapt_node {scalar_t__ ra_rix; scalar_t__ ra_last_raise; scalar_t__ ra_raise_interval; int /*<<< orphan*/  ra_nfail; TYPE_1__ ra_rates; int /*<<< orphan*/  ra_nok; } ;
struct ieee80211_ratectl_tx_status {int flags; int pktlen; int rssi; scalar_t__ status; } ;
struct ieee80211_node {struct ieee80211_rssadapt_node* ni_rctls; } ;

/* Variables and functions */
 int IEEE80211_RATECTL_STATUS_PKTLEN ; 
 int IEEE80211_RATECTL_STATUS_RSSI ; 
 scalar_t__ IEEE80211_RATECTL_TX_SUCCESS ; 
 int /*<<< orphan*/  rssadapt_lower_rate (struct ieee80211_rssadapt_node*,int,int) ; 
 int /*<<< orphan*/  rssadapt_raise_rate (struct ieee80211_rssadapt_node*,int,int) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void
rssadapt_tx_complete(const struct ieee80211_node *ni,
    const struct ieee80211_ratectl_tx_status *status)
{
	struct ieee80211_rssadapt_node *ra = ni->ni_rctls;
	int pktlen, rssi;

	if (!ra)
		return;

	if ((status->flags &
	    (IEEE80211_RATECTL_STATUS_PKTLEN|IEEE80211_RATECTL_STATUS_RSSI)) !=
	    (IEEE80211_RATECTL_STATUS_PKTLEN|IEEE80211_RATECTL_STATUS_RSSI))
		return;

	pktlen = status->pktlen;
	rssi = status->rssi;

	if (status->status == IEEE80211_RATECTL_TX_SUCCESS) {
		ra->ra_nok++;
		if ((ra->ra_rix + 1) < ra->ra_rates.rs_nrates &&
		    (ticks - ra->ra_last_raise) >= ra->ra_raise_interval)
			rssadapt_raise_rate(ra, pktlen, rssi);
	} else {
		ra->ra_nfail++;
		rssadapt_lower_rate(ra, pktlen, rssi);
	}
}