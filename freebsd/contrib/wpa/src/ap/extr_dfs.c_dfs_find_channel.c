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
struct hostapd_iface {TYPE_1__* conf; struct hostapd_hw_modes* current_mode; } ;
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_channel_data {int allowed_bw; int chan; } ;
struct TYPE_2__ {scalar_t__ secondary_channel; scalar_t__ ieee80211n; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_WIDTH_40P ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dfs_chan_range_available (struct hostapd_hw_modes*,int,int,int) ; 
 int dfs_get_used_n_chans (struct hostapd_iface*,int*) ; 
 int /*<<< orphan*/  dfs_is_chan_allowed (struct hostapd_channel_data*,int) ; 
 int /*<<< orphan*/  is_in_chanlist (struct hostapd_iface*,struct hostapd_channel_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dfs_find_channel(struct hostapd_iface *iface,
			    struct hostapd_channel_data **ret_chan,
			    int idx, int skip_radar)
{
	struct hostapd_hw_modes *mode;
	struct hostapd_channel_data *chan;
	int i, channel_idx = 0, n_chans, n_chans1;

	mode = iface->current_mode;
	n_chans = dfs_get_used_n_chans(iface, &n_chans1);

	wpa_printf(MSG_DEBUG, "DFS new chan checking %d channels", n_chans);
	for (i = 0; i < mode->num_channels; i++) {
		chan = &mode->channels[i];

		/* Skip HT40/VHT incompatible channels */
		if (iface->conf->ieee80211n &&
		    iface->conf->secondary_channel &&
		    (!dfs_is_chan_allowed(chan, n_chans) ||
		     !(chan->allowed_bw & HOSTAPD_CHAN_WIDTH_40P)))
			continue;

		/* Skip incompatible chandefs */
		if (!dfs_chan_range_available(mode, i, n_chans, skip_radar))
			continue;

		if (!is_in_chanlist(iface, chan))
			continue;

		if (ret_chan && idx == channel_idx) {
			wpa_printf(MSG_DEBUG, "Selected ch. #%d", chan->chan);
			*ret_chan = chan;
			return idx;
		}
		wpa_printf(MSG_DEBUG, "Adding channel: %d", chan->chan);
		channel_idx++;
	}
	return channel_idx;
}