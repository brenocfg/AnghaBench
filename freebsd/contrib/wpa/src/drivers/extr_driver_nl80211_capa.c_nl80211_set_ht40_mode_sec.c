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
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_channel_data {int flag; int freq; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_HT40 ; 
 int HOSTAPD_CHAN_HT40MINUS ; 
 int HOSTAPD_CHAN_HT40PLUS ; 

__attribute__((used)) static void nl80211_set_ht40_mode_sec(struct hostapd_hw_modes *mode, int start,
				      int end)
{
	int c;

	for (c = 0; c < mode->num_channels; c++) {
		struct hostapd_channel_data *chan = &mode->channels[c];
		if (!(chan->flag & HOSTAPD_CHAN_HT40))
			continue;
		if (chan->freq - 30 >= start && chan->freq - 10 <= end)
			chan->flag |= HOSTAPD_CHAN_HT40MINUS;
		if (chan->freq + 10 >= start && chan->freq + 30 <= end)
			chan->flag |= HOSTAPD_CHAN_HT40PLUS;
	}
}