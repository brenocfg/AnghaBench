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
typedef  size_t uint32_t ;
struct wlan_iface {size_t nchannels; size_t desired_channel; TYPE_1__* chanlist; int /*<<< orphan*/  wname; } ;
struct ieee80211_channel {scalar_t__ ic_ieee; scalar_t__ ic_flags; } ;
typedef  int /*<<< orphan*/  chan ;
struct TYPE_2__ {scalar_t__ ic_ieee; scalar_t__ ic_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_CURCHAN ; 
 int /*<<< orphan*/  memset (struct ieee80211_channel*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wlan_get_channel_list (struct wlan_iface*) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct ieee80211_channel*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wlan_config_get_dchannel(struct wlan_iface *wif)
{
	uint32_t i = 0;
	int val = 0;
	size_t argsize = sizeof(struct ieee80211_channel);
	struct ieee80211_channel chan;

	if (wlan_get_channel_list(wif) < 0)
		return (-1);

	memset(&chan, 0, sizeof(chan));
	if (wlan_ioctl(wif->wname, IEEE80211_IOC_CURCHAN, &val, &chan,
	    &argsize, 0) < 0)
		return (-1);

	for (i = 0; i < wif->nchannels; i++)
		if (chan.ic_ieee == wif->chanlist[i].ic_ieee &&
		    chan.ic_flags == wif->chanlist[i].ic_flags) {
			wif->desired_channel = i + 1;
			break;
		}

	return (0);
}