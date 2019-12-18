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
struct wlan_iface {int /*<<< orphan*/  desired_bssid; int /*<<< orphan*/  wname; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_IOC_BSSID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,char*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wlan_config_get_bssid(struct wlan_iface *wif)
{
	int val = 0;
	size_t argsize = IEEE80211_ADDR_LEN;
	char bssid[IEEE80211_ADDR_LEN];

	memset(bssid, 0, IEEE80211_ADDR_LEN);

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_BSSID, &val, bssid,
	    &argsize, 0) < 0 || argsize != IEEE80211_ADDR_LEN)
		return (-1);

	memcpy(wif->desired_bssid, bssid, IEEE80211_ADDR_LEN);

	return (0);
}