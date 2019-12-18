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
typedef  size_t u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int ieee80211_chan_to_freq (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int wpas_add_channel(u8 op_class, u8 chan, u8 num_primary_channels,
			    int *freqs)
{
	size_t i;

	for (i = 0; i < num_primary_channels; i++) {
		u8 primary_chan = chan - (2 * num_primary_channels - 2) + i * 4;

		freqs[i] = ieee80211_chan_to_freq(NULL, op_class, primary_chan);
		/* ieee80211_chan_to_freq() is not really meant for this
		 * conversion of 20 MHz primary channel numbers for wider VHT
		 * channels, so handle those as special cases here for now. */
		if (freqs[i] < 0 &&
		    (op_class == 128 || op_class == 129 || op_class == 130))
			freqs[i] = 5000 + 5 * primary_chan;
		if (freqs[i] < 0) {
			wpa_printf(MSG_DEBUG,
				   "Beacon Report: Invalid channel %u",
				   chan);
			return -1;
		}
	}

	return 0;
}