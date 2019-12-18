#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wlan_iface {int nchannels; struct ieee80211_channel* chanlist; int /*<<< orphan*/  htcaps; int /*<<< orphan*/  cryptocaps; int /*<<< orphan*/  drivercaps; int /*<<< orphan*/  wname; } ;
struct TYPE_2__ {int ic_nchans; int /*<<< orphan*/  ic_chans; } ;
struct ieee80211_devcaps_req {TYPE_1__ dc_chaninfo; int /*<<< orphan*/  dc_htcaps; int /*<<< orphan*/  dc_cryptocaps; int /*<<< orphan*/  dc_drivercaps; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_DEVCAPS ; 
 int /*<<< orphan*/  WLAN_SET_TDMA_OPMODE (struct wlan_iface*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_channel*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (struct ieee80211_devcaps_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlan_cryptocaps_to_snmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_drivercaps_to_snmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_htcaps_to_snmp (int /*<<< orphan*/ ) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct ieee80211_devcaps_req*,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_get_driver_caps(struct wlan_iface *wif)
{
	int val = 0;
	size_t argsize;
	struct ieee80211_devcaps_req dc;

	memset(&dc, 0, sizeof(struct ieee80211_devcaps_req));
	argsize = sizeof(struct ieee80211_devcaps_req);

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_DEVCAPS, &val, &dc,
	    &argsize, 0) < 0)
		return (-1);

	wif->drivercaps = wlan_drivercaps_to_snmp(dc.dc_drivercaps);
	wif->cryptocaps = wlan_cryptocaps_to_snmp(dc.dc_cryptocaps);
	wif->htcaps = wlan_htcaps_to_snmp(dc.dc_htcaps);

	WLAN_SET_TDMA_OPMODE(wif);

	argsize = dc.dc_chaninfo.ic_nchans * sizeof(struct ieee80211_channel);
	wif->chanlist = (struct ieee80211_channel *)malloc(argsize);
	if (wif->chanlist == NULL)
		return (0);

	memcpy(wif->chanlist, dc.dc_chaninfo.ic_chans, argsize);
	wif->nchannels = dc.dc_chaninfo.ic_nchans;

	return (0);
}