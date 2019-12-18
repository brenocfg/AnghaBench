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
struct hostapd_hw_modes {int dummy; } ;
struct hostapd_data {TYPE_1__* iface; } ;
struct TYPE_2__ {int num_hw_features; struct hostapd_hw_modes* hw_features; struct hostapd_hw_modes* current_mode; } ;

/* Variables and functions */
 int hw_get_chan (struct hostapd_hw_modes*,int) ; 

int hostapd_hw_get_channel(struct hostapd_data *hapd, int freq)
{
	int i, channel;
	struct hostapd_hw_modes *mode;

	if (hapd->iface->current_mode) {
		channel = hw_get_chan(hapd->iface->current_mode, freq);
		if (channel)
			return channel;
	}

	/* Check other available modes since the channel list for the current
	 * mode did not include the specified frequency. */
	if (!hapd->iface->hw_features)
		return 0;
	for (i = 0; i < hapd->iface->num_hw_features; i++) {
		mode = &hapd->iface->hw_features[i];
		channel = hw_get_chan(mode, freq);
		if (channel)
			return channel;
	}
	return 0;
}