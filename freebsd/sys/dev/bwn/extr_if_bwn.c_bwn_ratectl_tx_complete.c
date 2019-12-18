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
struct ieee80211_ratectl_tx_status {int long_retries; int /*<<< orphan*/  status; int /*<<< orphan*/  flags; } ;
struct ieee80211_node {int dummy; } ;
struct bwn_txstatus {int framecnt; scalar_t__ ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RATECTL_STATUS_LONG_RETRY ; 
 int /*<<< orphan*/  IEEE80211_RATECTL_TX_FAIL_UNSPECIFIED ; 
 int /*<<< orphan*/  IEEE80211_RATECTL_TX_SUCCESS ; 
 int /*<<< orphan*/  ieee80211_ratectl_tx_complete (struct ieee80211_node const*,struct ieee80211_ratectl_tx_status*) ; 

__attribute__((used)) static void
bwn_ratectl_tx_complete(const struct ieee80211_node *ni,
    const struct bwn_txstatus *status)
{
	struct ieee80211_ratectl_tx_status txs;
	int retrycnt = 0;

	/*
	 * If we don't get an ACK, then we should log the
	 * full framecnt.  That may be 0 if it's a PHY
	 * failure, so ensure that gets logged as some
	 * retry attempt.
	 */
	txs.flags = IEEE80211_RATECTL_STATUS_LONG_RETRY;
	if (status->ack) {
		txs.status = IEEE80211_RATECTL_TX_SUCCESS;
		retrycnt = status->framecnt - 1;
	} else {
		txs.status = IEEE80211_RATECTL_TX_FAIL_UNSPECIFIED;
		retrycnt = status->framecnt;
		if (retrycnt == 0)
			retrycnt = 1;
	}
	txs.long_retries = retrycnt;
	ieee80211_ratectl_tx_complete(ni, &txs);
}