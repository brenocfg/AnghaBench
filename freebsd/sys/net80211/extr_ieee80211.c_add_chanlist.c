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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int IEEE80211_CHAN_VHT ; 
 int IEEE80211_CHAN_VHT80 ; 
 int addchan (struct ieee80211_channel*,int,int*,scalar_t__ const,int,int /*<<< orphan*/ ,int) ; 
 int copychan_prev (struct ieee80211_channel*,int,int*,int) ; 
 int ieee80211_ieee2mhz (scalar_t__ const,int) ; 
 int /*<<< orphan*/  is_vht80_valid_freq (int) ; 

__attribute__((used)) static int
add_chanlist(struct ieee80211_channel chans[], int maxchans, int *nchans,
    const uint8_t ieee[], int nieee, uint32_t flags[])
{
	uint16_t freq;
	int i, j, error;
	int is_vht;

	for (i = 0; i < nieee; i++) {
		freq = ieee80211_ieee2mhz(ieee[i], flags[0]);
		for (j = 0; flags[j] != 0; j++) {
			/*
			 * Notes:
			 * + HT40 and VHT40 channels occur together, so
			 *   we need to be careful that we actually allow that.
			 * + VHT80, VHT160 will coexist with HT40/VHT40, so
			 *   make sure it's not skipped because of the overlap
			 *   check used for (V)HT40.
			 */
			is_vht = !! (flags[j] & IEEE80211_CHAN_VHT);

			/*
			 * Test for VHT80.
			 * XXX This is all very broken right now.
			 * What we /should/ do is:
			 *
			 * + check that the frequency is in the list of
			 *   allowed VHT80 ranges; and
			 * + the other 3 channels in the list are actually
			 *   also available.
			 */
			if (is_vht && flags[j] & IEEE80211_CHAN_VHT80)
				if (! is_vht80_valid_freq(freq))
					continue;

			/*
			 * Test for (V)HT40.
			 *
			 * This is also a fall through from VHT80; as we only
			 * allow a VHT80 channel if the VHT40 combination is
			 * also valid.  If the VHT40 form is not valid then
			 * we certainly can't do VHT80..
			 */
			if (flags[j] & IEEE80211_CHAN_HT40D)
				/*
				 * Can't have a "lower" channel if we are the
				 * first channel.
				 *
				 * Can't have a "lower" channel if it's below/
				 * within 20MHz of the first channel.
				 *
				 * Can't have a "lower" channel if the channel
				 * below it is not 20MHz away.
				 */
				if (i == 0 || ieee[i] < ieee[0] + 4 ||
				    freq - 20 !=
				    ieee80211_ieee2mhz(ieee[i] - 4, flags[j]))
					continue;
			if (flags[j] & IEEE80211_CHAN_HT40U)
				/*
				 * Can't have an "upper" channel if we are
				 * the last channel.
				 *
				 * Can't have an "upper" channel be above the
				 * last channel in the list.
				 *
				 * Can't have an "upper" channel if the next
				 * channel according to the math isn't 20MHz
				 * away.  (Likely for channel 13/14.)
				 */
				if (i == nieee - 1 ||
				    ieee[i] + 4 > ieee[nieee - 1] ||
				    freq + 20 !=
				    ieee80211_ieee2mhz(ieee[i] + 4, flags[j]))
					continue;

			if (j == 0) {
				error = addchan(chans, maxchans, nchans,
				    ieee[i], freq, 0, flags[j]);
			} else {
				error = copychan_prev(chans, maxchans, nchans,
				    flags[j]);
			}
			if (error != 0)
				return (error);
		}
	}

	return (0);
}