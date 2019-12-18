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
struct wlan_iface {int /*<<< orphan*/  txparams; int /*<<< orphan*/  wname; } ;
struct ieee80211_txparams_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_TXPARAMS ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_get_tx_params(struct wlan_iface *wif)
{
	int val = 0;
	size_t argsize;

	/*
	 * XXX: Reset IEEE80211_RATE_MCS bit on IEEE80211_MODE_11NA
	 * and IEEE80211_MODE_11NG modes.
	 */
	argsize = sizeof(struct ieee80211_txparams_req);
	if (wlan_ioctl(wif->wname, IEEE80211_IOC_TXPARAMS, &val,
	    &wif->txparams, &argsize, 0) < 0)
		return (-1);

	return (0);
}