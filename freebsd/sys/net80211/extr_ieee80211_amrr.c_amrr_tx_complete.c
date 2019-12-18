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
struct ieee80211_ratectl_tx_status {int flags; int long_retries; scalar_t__ status; } ;
struct ieee80211_node {struct ieee80211_amrr_node* ni_rctls; } ;
struct ieee80211_amrr_node {int amn_retrycnt; int /*<<< orphan*/  amn_success; int /*<<< orphan*/  amn_txcnt; } ;

/* Variables and functions */
 int IEEE80211_RATECTL_STATUS_LONG_RETRY ; 
 scalar_t__ IEEE80211_RATECTL_TX_SUCCESS ; 

__attribute__((used)) static void
amrr_tx_complete(const struct ieee80211_node *ni,
    const struct ieee80211_ratectl_tx_status *status)
{
	struct ieee80211_amrr_node *amn = ni->ni_rctls;
	int retries;

	if (!amn)
		return;

	retries = 0;
	if (status->flags & IEEE80211_RATECTL_STATUS_LONG_RETRY)
		retries = status->long_retries;

	amn->amn_txcnt++;
	if (status->status == IEEE80211_RATECTL_TX_SUCCESS)
		amn->amn_success++;
	amn->amn_retrycnt += retries;
}