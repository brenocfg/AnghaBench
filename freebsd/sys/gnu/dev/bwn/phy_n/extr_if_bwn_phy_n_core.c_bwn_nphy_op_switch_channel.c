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
struct ieee80211_channel {int dummy; } ;
struct bwn_mac {int dummy; } ;
typedef  int /*<<< orphan*/  bwn_chan_type_t ;

/* Variables and functions */
 scalar_t__ BWN_BAND_2G ; 
 int EINVAL ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_get_chan_type (struct bwn_mac*,int /*<<< orphan*/ *) ; 
 struct ieee80211_channel* bwn_get_channel (struct bwn_mac*) ; 
 int bwn_nphy_set_channel (struct bwn_mac*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 

int
bwn_nphy_op_switch_channel(struct bwn_mac *mac, unsigned int new_channel)
{
	struct ieee80211_channel *channel = bwn_get_channel(mac);
	bwn_chan_type_t channel_type = bwn_get_chan_type(mac, NULL);

	if (bwn_current_band(mac) == BWN_BAND_2G) {
		if ((new_channel < 1) || (new_channel > 14))
			return -EINVAL;
	} else {
		if (new_channel > 200)
			return -EINVAL;
	}

	return bwn_nphy_set_channel(mac, channel, channel_type);
}