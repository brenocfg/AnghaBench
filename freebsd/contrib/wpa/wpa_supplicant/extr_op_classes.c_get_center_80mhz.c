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
typedef  int u8 ;
struct hostapd_hw_modes {scalar_t__ mode; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 

__attribute__((used)) static int get_center_80mhz(struct hostapd_hw_modes *mode, u8 channel)
{
	u8 center_channels[] = { 42, 58, 106, 122, 138, 155 };
	size_t i;

	if (mode->mode != HOSTAPD_MODE_IEEE80211A)
		return 0;

	for (i = 0; i < ARRAY_SIZE(center_channels); i++) {
		/*
		 * In 80 MHz, the bandwidth "spans" 12 channels (e.g., 36-48),
		 * so the center channel is 6 channels away from the start/end.
		 */
		if (channel >= center_channels[i] - 6 &&
		    channel <= center_channels[i] + 6)
			return center_channels[i];
	}

	return 0;
}