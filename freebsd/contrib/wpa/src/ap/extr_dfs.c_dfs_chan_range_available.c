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
typedef  int /*<<< orphan*/  u32 ;
struct hostapd_hw_modes {int num_channels; struct hostapd_channel_data* channels; } ;
struct hostapd_channel_data {scalar_t__ freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan_bw_allowed (struct hostapd_channel_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  chan_pri_allowed (struct hostapd_channel_data*) ; 
 int /*<<< orphan*/  dfs_channel_available (struct hostapd_channel_data*,int) ; 
 struct hostapd_channel_data* dfs_get_chan_data (struct hostapd_hw_modes*,scalar_t__,int) ; 
 int /*<<< orphan*/  num_chan_to_bw (int) ; 

__attribute__((used)) static int dfs_chan_range_available(struct hostapd_hw_modes *mode,
				    int first_chan_idx, int num_chans,
				    int skip_radar)
{
	struct hostapd_channel_data *first_chan, *chan;
	int i;
	u32 bw = num_chan_to_bw(num_chans);

	if (first_chan_idx + num_chans > mode->num_channels)
		return 0;

	first_chan = &mode->channels[first_chan_idx];

	/* hostapd DFS implementation assumes the first channel as primary.
	 * If it's not allowed to use the first channel as primary, decline the
	 * whole channel range. */
	if (!chan_pri_allowed(first_chan))
		return 0;

	for (i = 0; i < num_chans; i++) {
		chan = dfs_get_chan_data(mode, first_chan->freq + i * 20,
					 first_chan_idx);
		if (!chan)
			return 0;

		/* HT 40 MHz secondary channel availability checked only for
		 * primary channel */
		if (!chan_bw_allowed(chan, bw, 1, !i))
			return 0;

		if (!dfs_channel_available(chan, skip_radar))
			return 0;
	}

	return 1;
}