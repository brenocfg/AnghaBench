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
struct wlan_iface {int hwmp_max_hops; int /*<<< orphan*/  wname; int /*<<< orphan*/  hwmp_root_mode; } ;

/* Variables and functions */
 int IEEE80211_HWMP_ROOTMODE_DISABLED ; 
 int IEEE80211_HWMP_ROOTMODE_NORMAL ; 
 int IEEE80211_HWMP_ROOTMODE_PROACTIVE ; 
 int IEEE80211_HWMP_ROOTMODE_RANN ; 
 int IEEE80211_IOC_HWMP_MAXHOPS ; 
 int IEEE80211_IOC_HWMP_ROOTMODE ; 
#define  LEAF_wlanHWMPMaxHops 133 
#define  LEAF_wlanHWMPRootMode 132 
#define  wlanHWMPRootMode_disabled 131 
#define  wlanHWMPRootMode_normal 130 
#define  wlanHWMPRootMode_proactive 129 
#define  wlanHWMPRootMode_rann 128 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,size_t*,int) ; 

int
wlan_hwmp_config_set(struct wlan_iface *wif, int which)
{
	int op, val = 0;
	size_t argsize = 0;

	switch (which) {
	case LEAF_wlanHWMPRootMode:
		op = IEEE80211_IOC_HWMP_ROOTMODE;
		switch (wif->hwmp_root_mode) {
		case wlanHWMPRootMode_disabled:
			val = IEEE80211_HWMP_ROOTMODE_DISABLED;
			break;
		case wlanHWMPRootMode_normal:
			val = IEEE80211_HWMP_ROOTMODE_NORMAL;
			break;
		case wlanHWMPRootMode_proactive:
			val = IEEE80211_HWMP_ROOTMODE_PROACTIVE;
			break;
		case wlanHWMPRootMode_rann:
			val = IEEE80211_HWMP_ROOTMODE_RANN;
			break;
		default:
			return (-1);
		}
		break;
	case LEAF_wlanHWMPMaxHops:
		op = IEEE80211_IOC_HWMP_MAXHOPS;
		val = wif->hwmp_max_hops;
		break;
	default:
		return (-1);
	}

	if (wlan_ioctl(wif->wname, op, &val, NULL, &argsize, 1) < 0)
		return (-1);

	return (0);
}