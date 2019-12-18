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
struct hostapd_channel_data {int flag; int allowed_bw; } ;

/* Variables and functions */
 int HOSTAPD_CHAN_DISABLED ; 
 int HOSTAPD_CHAN_WIDTH_20 ; 

int chan_pri_allowed(const struct hostapd_channel_data *chan)
{
	return !(chan->flag & HOSTAPD_CHAN_DISABLED) &&
		(chan->allowed_bw & HOSTAPD_CHAN_WIDTH_20);
}