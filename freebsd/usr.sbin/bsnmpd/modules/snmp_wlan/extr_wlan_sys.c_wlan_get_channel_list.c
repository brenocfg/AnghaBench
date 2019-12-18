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
typedef  size_t uint32_t ;
struct wlan_iface {size_t nchannels; struct ieee80211_channel* chanlist; int /*<<< orphan*/  wname; } ;
struct ieee80211req_chanlist {size_t ic_nchans; int /*<<< orphan*/  ic_channels; struct ieee80211_channel* ic_chans; } ;
struct ieee80211req_chaninfo {size_t ic_nchans; int /*<<< orphan*/  ic_channels; struct ieee80211_channel* ic_chans; } ;
struct ieee80211_channel {int /*<<< orphan*/  ic_ieee; } ;
typedef  int /*<<< orphan*/  active ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_CHANINFO ; 
 int /*<<< orphan*/  IEEE80211_IOC_CHANLIST ; 
 int WLAN_SNMP_MAX_CHANS ; 
 int /*<<< orphan*/  free (struct ieee80211req_chanlist*) ; 
 int /*<<< orphan*/  isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_channel*,struct ieee80211_channel const*,int) ; 
 scalar_t__ reallocf (struct ieee80211_channel*,size_t) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct ieee80211req_chanlist*,size_t*,int /*<<< orphan*/ ) ; 

int
wlan_get_channel_list(struct wlan_iface *wif)
{
	int val = 0;
	uint32_t i, nchans;
	size_t argsize;
	struct ieee80211req_chaninfo *chaninfo;
	struct ieee80211req_chanlist active;
	const struct ieee80211_channel *c;

	argsize = sizeof(struct ieee80211req_chaninfo) +
	    sizeof(struct ieee80211_channel) * WLAN_SNMP_MAX_CHANS;
	chaninfo = (struct ieee80211req_chaninfo *)malloc(argsize);
	if (chaninfo == NULL)
		return (-1);

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_CHANINFO, &val, chaninfo,
	    &argsize, 0) < 0)
		return (-1);

	argsize = sizeof(active);
	if (wlan_ioctl(wif->wname, IEEE80211_IOC_CHANLIST, &val, &active,
	    &argsize, 0) < 0)
		goto error;

	for (i = 0, nchans = 0; i < chaninfo->ic_nchans; i++) {
		c = &chaninfo->ic_chans[i];
		if (!isset(active.ic_channels, c->ic_ieee))
				continue;
		nchans++;
	}
	wif->chanlist = (struct ieee80211_channel *)reallocf(wif->chanlist,
	    nchans * sizeof(*c));
	if (wif->chanlist == NULL)
		goto error;
	wif->nchannels = nchans;
	for (i = 0, nchans = 0; i < chaninfo->ic_nchans; i++) {
		c = &chaninfo->ic_chans[i];
		if (!isset(active.ic_channels, c->ic_ieee))
				continue;
		memcpy(wif->chanlist + nchans, c, sizeof (*c));
		nchans++;
	}

	free(chaninfo);
	return (0);
error:
	wif->nchannels = 0;
	free(chaninfo);
	return (-1);
}