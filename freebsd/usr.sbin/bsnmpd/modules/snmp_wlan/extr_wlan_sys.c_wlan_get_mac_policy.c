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
struct wlan_iface {int macsupported; size_t mac_nacls; int /*<<< orphan*/  wname; void* mac_policy; } ;
struct ieee80211req_maclist {int dummy; } ;
struct ieee80211req {int /*<<< orphan*/  i_type; void* i_val; int /*<<< orphan*/  i_name; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IOC_MACCMD ; 
 int IEEE80211_MACCMD_LIST ; 
 void* IEEE80211_MACCMD_POLICY ; 
#define  IEEE80211_MACCMD_POLICY_ALLOW 131 
#define  IEEE80211_MACCMD_POLICY_DENY 130 
#define  IEEE80211_MACCMD_POLICY_OPEN 129 
#define  IEEE80211_MACCMD_POLICY_RADIUS 128 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCG80211 ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211req*) ; 
 int /*<<< orphan*/  memset (struct ieee80211req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* wlanMACAccessControlPolicy_allow ; 
 void* wlanMACAccessControlPolicy_deny ; 
 void* wlanMACAccessControlPolicy_open ; 
 void* wlanMACAccessControlPolicy_radius ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_get_mac_policy(struct wlan_iface *wif)
{
	int val = IEEE80211_MACCMD_POLICY;
	size_t argsize = 0;
	struct ieee80211req ireq;

	memset(&ireq, 0, sizeof(struct ieee80211req));
	strlcpy(ireq.i_name, wif->wname, IFNAMSIZ);
	ireq.i_type = IEEE80211_IOC_MACCMD;
	ireq.i_val = IEEE80211_MACCMD_POLICY;

	if (ioctl(sock, SIOCG80211, &ireq) < 0) {
		if (errno != EINVAL) {
			syslog(LOG_ERR, "iface %s - get param: ioctl(%d) "
			    "failed: %s", wif->wname, ireq.i_type,
			    strerror(errno));
			wif->macsupported = 0;
			return (-1);
		} else {
			wif->macsupported = 1;
			wif->mac_policy = wlanMACAccessControlPolicy_open;
			return (0);
		}

	}

	wif->macsupported = 1;

	switch (val) {
	case IEEE80211_MACCMD_POLICY_ALLOW:
		wif->mac_policy = wlanMACAccessControlPolicy_allow;
		break;
	case IEEE80211_MACCMD_POLICY_DENY:
		wif->mac_policy = wlanMACAccessControlPolicy_deny;
		break;
	case IEEE80211_MACCMD_POLICY_RADIUS:
		wif->mac_policy = wlanMACAccessControlPolicy_radius;
		break;
	case IEEE80211_MACCMD_POLICY_OPEN:
		/* FALLTHROUGH */
	default:
		wif->mac_policy = wlanMACAccessControlPolicy_open;
		break;
	}

	argsize = 0;
	val = IEEE80211_MACCMD_LIST;
	if (wlan_ioctl(wif->wname, IEEE80211_IOC_MACCMD, &val, NULL,
	    &argsize, 0) < 0)
		return (-1);

	wif->mac_nacls = argsize / sizeof(struct ieee80211req_maclist *);
	return (0);
}