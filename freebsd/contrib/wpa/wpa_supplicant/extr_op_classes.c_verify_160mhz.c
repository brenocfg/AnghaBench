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
struct hostapd_hw_modes {int dummy; } ;
typedef  enum chan_allowed { ____Placeholder_chan_allowed } chan_allowed ;

/* Variables and functions */
 int ALLOWED ; 
 unsigned int HOSTAPD_CHAN_NO_IR ; 
 unsigned int HOSTAPD_CHAN_VHT_10_150 ; 
 unsigned int HOSTAPD_CHAN_VHT_110_50 ; 
 unsigned int HOSTAPD_CHAN_VHT_130_30 ; 
 unsigned int HOSTAPD_CHAN_VHT_150_10 ; 
 unsigned int HOSTAPD_CHAN_VHT_30_130 ; 
 unsigned int HOSTAPD_CHAN_VHT_50_110 ; 
 unsigned int HOSTAPD_CHAN_VHT_70_90 ; 
 unsigned int HOSTAPD_CHAN_VHT_90_70 ; 
 int NOT_ALLOWED ; 
 int NO_IR ; 
 int allow_channel (struct hostapd_hw_modes*,int,unsigned int*) ; 
 int get_center_160mhz (struct hostapd_hw_modes*,int) ; 

__attribute__((used)) static enum chan_allowed verify_160mhz(struct hostapd_hw_modes *mode,
				       u8 channel)
{
	u8 center_chan;
	unsigned int i;
	unsigned int no_ir = 0;

	center_chan = get_center_160mhz(mode, channel);
	if (!center_chan)
		return NOT_ALLOWED;

	/* Check all the channels are available */
	for (i = 0; i < 8; i++) {
		unsigned int flags;
		u8 adj_chan = center_chan - 14 + i * 4;

		if (allow_channel(mode, adj_chan, &flags) == NOT_ALLOWED)
			return NOT_ALLOWED;

		if ((i == 0 && !(flags & HOSTAPD_CHAN_VHT_10_150)) ||
		    (i == 1 && !(flags & HOSTAPD_CHAN_VHT_30_130)) ||
		    (i == 2 && !(flags & HOSTAPD_CHAN_VHT_50_110)) ||
		    (i == 3 && !(flags & HOSTAPD_CHAN_VHT_70_90)) ||
		    (i == 4 && !(flags & HOSTAPD_CHAN_VHT_90_70)) ||
		    (i == 5 && !(flags & HOSTAPD_CHAN_VHT_110_50)) ||
		    (i == 6 && !(flags & HOSTAPD_CHAN_VHT_130_30)) ||
		    (i == 7 && !(flags & HOSTAPD_CHAN_VHT_150_10)))
			return NOT_ALLOWED;

		if (flags & HOSTAPD_CHAN_NO_IR)
			no_ir = 1;
	}

	if (no_ir)
		return NO_IR;

	return ALLOWED;
}