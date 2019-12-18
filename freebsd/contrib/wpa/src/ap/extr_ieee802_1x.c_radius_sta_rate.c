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
struct sta_info {int supported_rates_len; int* supported_rates; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */

int radius_sta_rate(struct hostapd_data *hapd, struct sta_info *sta)
{
	int i;
	u8 rate = 0;

	for (i = 0; i < sta->supported_rates_len; i++)
		if ((sta->supported_rates[i] & 0x7f) > rate)
			rate = sta->supported_rates[i] & 0x7f;

	return rate;
}