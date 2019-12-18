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
typedef  int u32 ;
struct hostapd_channel_data {int allowed_bw; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_WIDTH_160 ; 
 int HOSTAPD_CHAN_WIDTH_20 ; 
 int HOSTAPD_CHAN_WIDTH_40M ; 
 int HOSTAPD_CHAN_WIDTH_40P ; 
 int HOSTAPD_CHAN_WIDTH_80 ; 

int chan_bw_allowed(const struct hostapd_channel_data *chan, u32 bw,
		    int ht40_plus, int pri)
{
	u32 bw_mask;

	switch (bw) {
	case 20:
		bw_mask = HOSTAPD_CHAN_WIDTH_20;
		break;
	case 40:
		/* HT 40 MHz support declared only for primary channel,
		 * just skip 40 MHz secondary checking */
		if (pri && ht40_plus)
			bw_mask = HOSTAPD_CHAN_WIDTH_40P;
		else if (pri && !ht40_plus)
			bw_mask = HOSTAPD_CHAN_WIDTH_40M;
		else
			bw_mask = 0;
		break;
	case 80:
		bw_mask = HOSTAPD_CHAN_WIDTH_80;
		break;
	case 160:
		bw_mask = HOSTAPD_CHAN_WIDTH_160;
		break;
	default:
		bw_mask = 0;
		break;
	}

	return (chan->allowed_bw & bw_mask) == bw_mask;
}