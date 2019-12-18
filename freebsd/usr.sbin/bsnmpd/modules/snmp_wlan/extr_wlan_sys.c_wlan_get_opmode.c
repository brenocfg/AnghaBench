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
struct wlan_iface {int /*<<< orphan*/  mode; int /*<<< orphan*/  wname; } ;
struct ifmediareq {int ifm_current; int /*<<< orphan*/  ifm_name; } ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 int IFM_FLAG0 ; 
 int IFM_IEEE80211_ADHOC ; 
 int IFM_IEEE80211_HOSTAP ; 
 int IFM_IEEE80211_MBSS ; 
 int IFM_IEEE80211_MONITOR ; 
 int IFM_IEEE80211_WDS ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_adhocDemo ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_hostAp ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_ibss ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_meshPoint ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_monitor ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_station ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_wds ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifmediareq*) ; 
 int /*<<< orphan*/  memset (struct ifmediareq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
wlan_get_opmode(struct wlan_iface *wif)
{
	struct ifmediareq ifmr;

	memset(&ifmr, 0, sizeof(struct ifmediareq));
	strlcpy(ifmr.ifm_name, wif->wname, sizeof(ifmr.ifm_name));

	if (ioctl(sock, SIOCGIFMEDIA, &ifmr) < 0) {
		if (errno == ENXIO)
			return (-1);
		wif->mode = WlanIfaceOperatingModeType_station;
		return (0);
	}

	if (ifmr.ifm_current & IFM_IEEE80211_ADHOC) {
		if (ifmr.ifm_current & IFM_FLAG0)
			wif->mode = WlanIfaceOperatingModeType_adhocDemo;
		else
			wif->mode = WlanIfaceOperatingModeType_ibss;
	} else if (ifmr.ifm_current & IFM_IEEE80211_HOSTAP)
		wif->mode = WlanIfaceOperatingModeType_hostAp;
	else if (ifmr.ifm_current & IFM_IEEE80211_MONITOR)
		wif->mode = WlanIfaceOperatingModeType_monitor;
	else if (ifmr.ifm_current & IFM_IEEE80211_MBSS)
		wif->mode = WlanIfaceOperatingModeType_meshPoint;
	else if (ifmr.ifm_current & IFM_IEEE80211_WDS)
		wif->mode = WlanIfaceOperatingModeType_wds;

	return (0);
}