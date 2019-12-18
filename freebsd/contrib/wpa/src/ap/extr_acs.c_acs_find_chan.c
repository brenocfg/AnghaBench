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
struct hostapd_iface {TYPE_1__* current_mode; } ;
struct hostapd_channel_data {int flag; int freq; } ;
struct TYPE_2__ {int num_channels; struct hostapd_channel_data* channels; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 

__attribute__((used)) static struct hostapd_channel_data *acs_find_chan(struct hostapd_iface *iface,
						  int freq)
{
	struct hostapd_channel_data *chan;
	int i;

	for (i = 0; i < iface->current_mode->num_channels; i++) {
		chan = &iface->current_mode->channels[i];

		if (chan->flag & HOSTAPD_CHAN_DISABLED)
			continue;

		if (chan->freq == freq)
			return chan;
	}

	return NULL;
}