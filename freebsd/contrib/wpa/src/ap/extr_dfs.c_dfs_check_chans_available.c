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
struct hostapd_iface {struct hostapd_hw_modes* current_mode; } ;
struct hostapd_hw_modes {struct hostapd_channel_data* channels; } ;
struct hostapd_channel_data {int flag; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DFS_AVAILABLE ; 
 int HOSTAPD_CHAN_DFS_MASK ; 
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_RADAR ; 

__attribute__((used)) static int dfs_check_chans_available(struct hostapd_iface *iface,
				     int start_chan_idx, int n_chans)
{
	struct hostapd_channel_data *channel;
	struct hostapd_hw_modes *mode;
	int i;

	mode = iface->current_mode;

	for (i = 0; i < n_chans; i++) {
		channel = &mode->channels[start_chan_idx + i];

		if (channel->flag & HOSTAPD_CHAN_DISABLED)
			break;

		if (!(channel->flag & HOSTAPD_CHAN_RADAR))
			continue;

		if ((channel->flag & HOSTAPD_CHAN_DFS_MASK) !=
		    HOSTAPD_CHAN_DFS_AVAILABLE)
			break;
	}

	return i == n_chans;
}