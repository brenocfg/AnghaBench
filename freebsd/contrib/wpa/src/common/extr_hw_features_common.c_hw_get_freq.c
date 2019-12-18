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
struct hostapd_hw_modes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_get_channel_chan (struct hostapd_hw_modes*,int,int*) ; 

int hw_get_freq(struct hostapd_hw_modes *mode, int chan)
{
	int freq;

	hw_get_channel_chan(mode, chan, &freq);

	return freq;
}