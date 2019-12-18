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
struct wlan_iface {int /*<<< orphan*/  scan_status; int /*<<< orphan*/  wname; int /*<<< orphan*/  scan_maxdwell; int /*<<< orphan*/  scan_mindwell; int /*<<< orphan*/  scan_duration; int /*<<< orphan*/  scan_flags; } ;
struct ieee80211_scan_req {scalar_t__ sr_nssid; int /*<<< orphan*/  sr_maxdwell; int /*<<< orphan*/  sr_mindwell; int /*<<< orphan*/  sr_duration; int /*<<< orphan*/  sr_flags; } ;
typedef  int /*<<< orphan*/  sr ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_SCAN_BGSCAN ; 
 int /*<<< orphan*/  IEEE80211_IOC_SCAN_REQ ; 
 int /*<<< orphan*/  memset (struct ieee80211_scan_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlanScanConfigStatus_running ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct ieee80211_scan_req*,size_t*,int) ; 
 int /*<<< orphan*/  wlan_snmp_to_scan_flags (int /*<<< orphan*/ ) ; 

int
wlan_set_scan_config(struct wlan_iface *wif)
{
	int val = 0;
	size_t argsize;
	struct ieee80211_scan_req sr;


	memset(&sr, 0, sizeof(sr));
	argsize = sizeof(struct ieee80211_scan_req);
	sr.sr_flags = wlan_snmp_to_scan_flags(wif->scan_flags);
	sr.sr_flags |= IEEE80211_IOC_SCAN_BGSCAN;
	sr.sr_duration = wif->scan_duration;
	sr.sr_mindwell = wif->scan_mindwell;
	sr.sr_maxdwell = wif->scan_maxdwell;
	sr.sr_nssid = 0;

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_SCAN_REQ,
	    &val, &sr, &argsize, 1) < 0)
		return (-1);

	wif->scan_status = wlanScanConfigStatus_running;
	return (0);
}