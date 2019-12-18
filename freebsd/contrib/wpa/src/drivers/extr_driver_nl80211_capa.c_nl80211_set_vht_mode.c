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
struct hostapd_channel_data {int freq; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_10_150 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_10_70 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_110_50 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_130_30 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_150_10 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_30_130 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_30_50 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_50_110 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_50_30 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_70_10 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_70_90 ; 
 int /*<<< orphan*/  HOSTAPD_CHAN_VHT_90_70 ; 

__attribute__((used)) static void nl80211_set_vht_mode(struct hostapd_hw_modes *mode, int start,
				 int end, int max_bw)
{
	int c;

	for (c = 0; c < mode->num_channels; c++) {
		struct hostapd_channel_data *chan = &mode->channels[c];
		if (chan->freq - 10 >= start && chan->freq + 70 <= end)
			chan->flag |= HOSTAPD_CHAN_VHT_10_70;

		if (chan->freq - 30 >= start && chan->freq + 50 <= end)
			chan->flag |= HOSTAPD_CHAN_VHT_30_50;

		if (chan->freq - 50 >= start && chan->freq + 30 <= end)
			chan->flag |= HOSTAPD_CHAN_VHT_50_30;

		if (chan->freq - 70 >= start && chan->freq + 10 <= end)
			chan->flag |= HOSTAPD_CHAN_VHT_70_10;

		if (max_bw >= 160) {
			if (chan->freq - 10 >= start && chan->freq + 150 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_10_150;

			if (chan->freq - 30 >= start && chan->freq + 130 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_30_130;

			if (chan->freq - 50 >= start && chan->freq + 110 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_50_110;

			if (chan->freq - 70 >= start && chan->freq + 90 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_70_90;

			if (chan->freq - 90 >= start && chan->freq + 70 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_90_70;

			if (chan->freq - 110 >= start && chan->freq + 50 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_110_50;

			if (chan->freq - 130 >= start && chan->freq + 30 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_130_30;

			if (chan->freq - 150 >= start && chan->freq + 10 <= end)
				chan->flag |= HOSTAPD_CHAN_VHT_150_10;
		}
	}
}