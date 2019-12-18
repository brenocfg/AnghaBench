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
struct wlan_iface {scalar_t__ mode; char* desired_ssid; int /*<<< orphan*/  wname; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_MESH_ID ; 
 int /*<<< orphan*/  IEEE80211_IOC_SSID ; 
 size_t IEEE80211_NWID_LEN ; 
 scalar_t__ WlanIfaceOperatingModeType_meshPoint ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,char*,size_t*,int) ; 

int
wlan_config_set_dssid(struct wlan_iface *wif, char *ssid, int slen)
{
	int val = 0;
	size_t argsize = slen;

	if (wlan_ioctl(wif->wname,
	    (wif->mode == WlanIfaceOperatingModeType_meshPoint) ?
	    IEEE80211_IOC_MESH_ID : IEEE80211_IOC_SSID, &val, ssid,
	    &argsize, 1) < 0)
		return (-1);

	if (argsize > IEEE80211_NWID_LEN)
		argsize = IEEE80211_NWID_LEN;
	memcpy(wif->desired_ssid, ssid, argsize);
	wif->desired_ssid[argsize] = '\0';

	return (0);
}