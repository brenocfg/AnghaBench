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

/* Variables and functions */
 int ieee80211_chan_to_freq (int /*<<< orphan*/ *,int,int) ; 

int p2p_channel_to_freq(int op_class, int channel)
{
	return ieee80211_chan_to_freq(NULL, op_class, channel);
}