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
struct hostapd_iface {int /*<<< orphan*/  current_mode; } ;
struct hostapd_channel_data {int flag; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_NO_IR ; 
 int HOSTAPD_CHAN_RADAR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ chan_pri_allowed (struct hostapd_channel_data*) ; 
 struct hostapd_channel_data* hw_get_channel_chan (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,char*,int,char*,char*) ; 

__attribute__((used)) static int hostapd_is_usable_chan(struct hostapd_iface *iface,
				  int channel, int primary)
{
	struct hostapd_channel_data *chan;

	if (!iface->current_mode)
		return 0;

	chan = hw_get_channel_chan(iface->current_mode, channel, NULL);
	if (!chan)
		return 0;

	if ((primary && chan_pri_allowed(chan)) ||
	    (!primary && !(chan->flag & HOSTAPD_CHAN_DISABLED)))
		return 1;

	wpa_printf(MSG_INFO,
		   "Channel %d (%s) not allowed for AP mode, flags: 0x%x%s%s",
		   channel, primary ? "primary" : "secondary",
		   chan->flag,
		   chan->flag & HOSTAPD_CHAN_NO_IR ? " NO-IR" : "",
		   chan->flag & HOSTAPD_CHAN_RADAR ? " RADAR" : "");
	return 0;
}