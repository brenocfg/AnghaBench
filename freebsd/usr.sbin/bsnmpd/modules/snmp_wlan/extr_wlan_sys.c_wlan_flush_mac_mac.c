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
struct wlan_iface {int /*<<< orphan*/  wname; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_MACCMD ; 
 int IEEE80211_MACCMD_FLUSH ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int) ; 

int
wlan_flush_mac_mac(struct wlan_iface *wif)
{
	int val = IEEE80211_MACCMD_FLUSH;
	size_t argsize = 0;

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_MACCMD, &val, NULL,
	    &argsize, 1) < 0)
		return (-1);

	return (0);
}