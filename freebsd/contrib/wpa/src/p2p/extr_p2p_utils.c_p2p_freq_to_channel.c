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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ NUM_HOSTAPD_MODES ; 
 scalar_t__ ieee80211_freq_to_channel_ext (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int p2p_freq_to_channel(unsigned int freq, u8 *op_class, u8 *channel)
{
	if (ieee80211_freq_to_channel_ext(freq, 0, 0, op_class, channel) ==
	    NUM_HOSTAPD_MODES)
		return -1;

	return 0;
}