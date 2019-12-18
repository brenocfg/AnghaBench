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
struct wlan_iface {int hwmp_max_hops; int /*<<< orphan*/  hwmp_root_mode; int /*<<< orphan*/  wname; } ;

/* Variables and functions */
#define  IEEE80211_HWMP_ROOTMODE_DISABLED 133 
#define  IEEE80211_HWMP_ROOTMODE_NORMAL 132 
#define  IEEE80211_HWMP_ROOTMODE_PROACTIVE 131 
#define  IEEE80211_HWMP_ROOTMODE_RANN 130 
 int IEEE80211_IOC_HWMP_MAXHOPS ; 
 int IEEE80211_IOC_HWMP_ROOTMODE ; 
#define  LEAF_wlanHWMPMaxHops 129 
#define  LEAF_wlanHWMPRootMode 128 
 int /*<<< orphan*/  wlanHWMPRootMode_disabled ; 
 int /*<<< orphan*/  wlanHWMPRootMode_normal ; 
 int /*<<< orphan*/  wlanHWMPRootMode_proactive ; 
 int /*<<< orphan*/  wlanHWMPRootMode_rann ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_hwmp_config_get(struct wlan_iface *wif, int which)
{
	int op, val = 0;
	size_t argsize = 0;

	switch (which) {
	case LEAF_wlanHWMPRootMode:
		op = IEEE80211_IOC_HWMP_ROOTMODE;
		break;
	case LEAF_wlanHWMPMaxHops:
		op = IEEE80211_IOC_HWMP_MAXHOPS;
		break;
	default:
		return (-1);
	}

	if (wlan_ioctl(wif->wname, op, &val, NULL, &argsize, 0) < 0)
		return (-1);

	switch (which) {
	case LEAF_wlanHWMPRootMode:
		switch (val) {
		case IEEE80211_HWMP_ROOTMODE_NORMAL:
			wif->hwmp_root_mode = wlanHWMPRootMode_normal;
			break;
		case IEEE80211_HWMP_ROOTMODE_PROACTIVE:
			wif->hwmp_root_mode = wlanHWMPRootMode_proactive;
			break;
		case IEEE80211_HWMP_ROOTMODE_RANN:
			wif->hwmp_root_mode = wlanHWMPRootMode_rann;
			break;
		case IEEE80211_HWMP_ROOTMODE_DISABLED:
		default:
			wif->hwmp_root_mode = wlanHWMPRootMode_disabled;
			break;
		}
		break;
	case LEAF_wlanHWMPMaxHops:
		wif->hwmp_max_hops = val;
		break;
	}

	return (0);
}