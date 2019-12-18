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
struct wlan_iface {int wepmode; int /*<<< orphan*/  wname; int /*<<< orphan*/  wepsupported; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_WEP ; 
 int IEEE80211_WEP_MIXED ; 
 int IEEE80211_WEP_OFF ; 
 int IEEE80211_WEP_ON ; 
#define  wlanWepMode_mixed 130 
#define  wlanWepMode_off 129 
#define  wlanWepMode_on 128 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int) ; 

int
wlan_set_wepmode(struct wlan_iface *wif)
{
	int val;
	size_t argsize = 0;

	if (!wif->wepsupported)
		return (-1);

	switch (wif->wepmode) {
	case wlanWepMode_off:
		val = IEEE80211_WEP_OFF;
		break;
	case wlanWepMode_on:
		val = IEEE80211_WEP_ON;
		break;
	case wlanWepMode_mixed:
		val = IEEE80211_WEP_MIXED;
		break;
	default:
		return (-1);
	}

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_WEP, &val, NULL,
	    &argsize, 1) < 0)
		return (-1);

	return (0);
}