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
struct wlan_iface {int mac_policy; int /*<<< orphan*/  wname; int /*<<< orphan*/  macsupported; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_MACCMD ; 
 int IEEE80211_MACCMD_POLICY_ALLOW ; 
 int IEEE80211_MACCMD_POLICY_DENY ; 
 int IEEE80211_MACCMD_POLICY_OPEN ; 
 int IEEE80211_MACCMD_POLICY_RADIUS ; 
#define  wlanMACAccessControlPolicy_allow 131 
#define  wlanMACAccessControlPolicy_deny 130 
#define  wlanMACAccessControlPolicy_open 129 
#define  wlanMACAccessControlPolicy_radius 128 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int) ; 

int
wlan_set_mac_policy(struct wlan_iface *wif)
{
	int val;
	size_t argsize = 0;

	if (!wif->macsupported)
		return (-1);

	switch (wif->mac_policy) {
	case wlanMACAccessControlPolicy_allow:
		val = IEEE80211_MACCMD_POLICY_ALLOW;
		break;
	case wlanMACAccessControlPolicy_deny:
		val = IEEE80211_MACCMD_POLICY_DENY;
		break;
	case wlanMACAccessControlPolicy_radius:
		val = IEEE80211_MACCMD_POLICY_RADIUS;
		break;
	case wlanMACAccessControlPolicy_open:
		val = IEEE80211_MACCMD_POLICY_OPEN;
		break;
	default:
		return (-1);
	}

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_MACCMD, &val, NULL,
	    &argsize, 1) < 0)
		return (-1);

	return (0);
}