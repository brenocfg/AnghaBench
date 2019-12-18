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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct phy_info_arg {size_t* num_modes; struct hostapd_hw_modes* modes; } ;
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_channel_data {scalar_t__ max_tx_power; scalar_t__ freq; } ;

/* Variables and functions */

__attribute__((used)) static void nl80211_reg_rule_max_eirp(u32 start, u32 end, u32 max_eirp,
				      struct phy_info_arg *results)
{
	u16 m;

	for (m = 0; m < *results->num_modes; m++) {
		int c;
		struct hostapd_hw_modes *mode = &results->modes[m];

		for (c = 0; c < mode->num_channels; c++) {
			struct hostapd_channel_data *chan = &mode->channels[c];
			if ((u32) chan->freq - 10 >= start &&
			    (u32) chan->freq + 10 <= end)
				chan->max_tx_power = max_eirp;
		}
	}
}