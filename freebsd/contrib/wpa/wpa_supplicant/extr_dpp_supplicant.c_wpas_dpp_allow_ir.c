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
struct TYPE_2__ {int num_modes; struct hostapd_hw_modes* modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_channel_data {int freq; int flag; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_NO_IR ; 
 int HOSTAPD_CHAN_RADAR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int wpas_dpp_allow_ir(struct wpa_supplicant *wpa_s, unsigned int freq)
{
	int i, j;

	if (!wpa_s->hw.modes)
		return -1;

	for (i = 0; i < wpa_s->hw.num_modes; i++) {
		struct hostapd_hw_modes *mode = &wpa_s->hw.modes[i];

		for (j = 0; j < mode->num_channels; j++) {
			struct hostapd_channel_data *chan = &mode->channels[j];

			if (chan->freq != (int) freq)
				continue;

			if (chan->flag & (HOSTAPD_CHAN_DISABLED |
					  HOSTAPD_CHAN_NO_IR |
					  HOSTAPD_CHAN_RADAR))
				continue;

			return 1;
		}
	}

	wpa_printf(MSG_DEBUG,
		   "DPP: Frequency %u MHz not supported or does not allow PKEX initiation in the current channel list",
		   freq);

	return 0;
}