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
struct wpa_supplicant {scalar_t__ off_channel_freq; } ;

/* Variables and functions */

void offchannel_cancel_remain_on_channel_cb(struct wpa_supplicant *wpa_s,
					    unsigned int freq)
{
	wpa_s->off_channel_freq = 0;
}