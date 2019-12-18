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
typedef  int /*<<< orphan*/  uint8_t ;
struct wlan_iface {int /*<<< orphan*/  desired_bssid; int /*<<< orphan*/  wname; } ;

/* Variables and functions */
 size_t IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_IOC_BSSID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int) ; 

__attribute__((used)) static int
wlan_config_set_bssid(struct wlan_iface *wif, uint8_t *bssid)
{
	int val = 0;
	size_t argsize = IEEE80211_ADDR_LEN;

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_BSSID, &val, bssid,
	    &argsize, 1) < 0 || argsize != IEEE80211_ADDR_LEN)
		return (-1);

	memcpy(wif->desired_bssid, bssid, IEEE80211_ADDR_LEN);

	return (0);
}