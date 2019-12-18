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
typedef  int u8 ;
struct wpa_global {int dummy; } ;
struct hostapd_hw_modes {scalar_t__ mode; int num_channels; TYPE_1__* channels; } ;
struct TYPE_2__ {int chan; int flag; } ;

/* Variables and functions */
 int ALLOWED ; 
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_NO_IR ; 
 int HOSTAPD_CHAN_RADAR ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 int NOT_ALLOWED ; 
 int NO_IR ; 
 scalar_t__ wpas_p2p_disallowed_freq (struct wpa_global*,unsigned int) ; 

__attribute__((used)) static int has_channel(struct wpa_global *global,
		       struct hostapd_hw_modes *mode, u8 chan, int *flags)
{
	int i;
	unsigned int freq;

	freq = (mode->mode == HOSTAPD_MODE_IEEE80211A ? 5000 : 2407) +
		chan * 5;
	if (wpas_p2p_disallowed_freq(global, freq))
		return NOT_ALLOWED;

	for (i = 0; i < mode->num_channels; i++) {
		if (mode->channels[i].chan == chan) {
			if (flags)
				*flags = mode->channels[i].flag;
			if (mode->channels[i].flag &
			    (HOSTAPD_CHAN_DISABLED |
			     HOSTAPD_CHAN_RADAR))
				return NOT_ALLOWED;
			if (mode->channels[i].flag & HOSTAPD_CHAN_NO_IR)
				return NO_IR;
			return ALLOWED;
		}
	}

	return NOT_ALLOWED;
}