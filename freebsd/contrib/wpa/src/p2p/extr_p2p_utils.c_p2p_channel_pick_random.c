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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 scalar_t__ os_get_random (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static u8 p2p_channel_pick_random(const u8 *channels, unsigned int num_channels)
{
	unsigned int r;
	if (os_get_random((u8 *) &r, sizeof(r)) < 0)
		r = 0;
	r %= num_channels;
	return channels[r];
}