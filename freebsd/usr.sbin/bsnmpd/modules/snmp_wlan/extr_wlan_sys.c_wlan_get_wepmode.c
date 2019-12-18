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
struct wlan_iface {int wepsupported; void* wepmode; scalar_t__ weptxkey; int /*<<< orphan*/  wname; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_WEP ; 
#define  IEEE80211_WEP_MIXED 130 
 int IEEE80211_WEP_NOSUP ; 
#define  IEEE80211_WEP_OFF 129 
#define  IEEE80211_WEP_ON 128 
 void* wlanWepMode_mixed ; 
 void* wlanWepMode_off ; 
 void* wlanWepMode_on ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_get_wepmode(struct wlan_iface *wif)
{
	int val = 0;
	size_t argsize = 0;

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_WEP, &val, NULL,
	    &argsize, 0) < 0 || val == IEEE80211_WEP_NOSUP) {
		wif->wepsupported = 0; /* XXX */
		wif->wepmode = wlanWepMode_off;
		wif->weptxkey = 0;
		return (-1);
	}

	wif->wepsupported = 1;

	switch (val) {
	case IEEE80211_WEP_ON:
		wif->wepmode = wlanWepMode_on;
		break;
	case IEEE80211_WEP_MIXED:
		wif->wepmode = wlanWepMode_mixed;
		break;
	case IEEE80211_WEP_OFF:
		/* FALLTHROUGH */
	default:
		wif->wepmode = wlanWepMode_off;
		break;
	}

	return (0);
}