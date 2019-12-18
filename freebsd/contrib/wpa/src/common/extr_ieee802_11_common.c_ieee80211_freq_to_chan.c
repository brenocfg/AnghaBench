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
typedef  enum hostapd_hw_mode { ____Placeholder_hostapd_hw_mode } hostapd_hw_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CHANWIDTH_USE_HT ; 
 int ieee80211_freq_to_channel_ext (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum hostapd_hw_mode ieee80211_freq_to_chan(int freq, u8 *channel)
{
	u8 op_class;

	return ieee80211_freq_to_channel_ext(freq, 0, CHANWIDTH_USE_HT,
					     &op_class, channel);
}