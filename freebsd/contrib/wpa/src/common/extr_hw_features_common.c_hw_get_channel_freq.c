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
struct hostapd_channel_data {int freq; int chan; } ;

/* Variables and functions */

struct hostapd_channel_data * hw_get_channel_freq(struct hostapd_hw_modes *mode,
						  int freq, int *chan)
{
	int i;

	if (chan)
		*chan = 0;

	if (!mode)
		return NULL;

	for (i = 0; i < mode->num_channels; i++) {
		struct hostapd_channel_data *ch = &mode->channels[i];
		if (ch->freq == freq) {
			if (chan)
				*chan = ch->chan;
			return ch;
		}
	}

	return NULL;
}