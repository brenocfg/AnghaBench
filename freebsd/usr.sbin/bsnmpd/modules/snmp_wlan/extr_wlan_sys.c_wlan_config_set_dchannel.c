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
typedef  scalar_t__ uint32_t ;
struct wlan_iface {scalar_t__ nchannels; scalar_t__ chanlist; scalar_t__ desired_channel; int /*<<< orphan*/  wname; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int /*<<< orphan*/  chan ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_CURCHAN ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_channel*,scalar_t__,int) ; 
 scalar_t__ wlan_get_channel_list (struct wlan_iface*) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct ieee80211_channel*,size_t*,int) ; 

__attribute__((used)) static int
wlan_config_set_dchannel(struct wlan_iface *wif, uint32_t dchannel)
{
	int val = 0;
	size_t argsize = sizeof(struct ieee80211_channel);
	struct ieee80211_channel chan;

	if (wlan_get_channel_list(wif) < 0)
		return (-1);

	if (dchannel > wif->nchannels)
		return (-1);

	memcpy(&chan, wif->chanlist + dchannel - 1, sizeof(chan));
	if (wlan_ioctl(wif->wname, IEEE80211_IOC_CURCHAN, &val, &chan,
	    &argsize, 1) < 0)
		return (-1);

	wif->desired_channel = dchannel;

	return (0);
}