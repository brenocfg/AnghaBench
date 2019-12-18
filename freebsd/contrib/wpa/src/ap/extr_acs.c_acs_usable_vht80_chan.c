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
struct hostapd_channel_data {int const chan; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 

__attribute__((used)) static int acs_usable_vht80_chan(const struct hostapd_channel_data *chan)
{
	const int allowed[] = { 36, 52, 100, 116, 132, 149 };
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(allowed); i++)
		if (chan->chan == allowed[i])
			return 1;

	return 0;
}