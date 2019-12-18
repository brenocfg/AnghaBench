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
typedef  int uint32_t ;
typedef  int int32_t ;

/* Variables and functions */

int32_t
usb_ts_rand_noise(void)
{
	uint32_t temp;
	const uint32_t prime = 0xFFFF1D;
	static uint32_t noise_rem = 1;

	if (noise_rem & 1) {
		noise_rem += prime;
	}
	noise_rem /= 2;

	temp = noise_rem;

	/* unsigned to signed conversion */

	temp ^= 0x800000;
	if (temp & 0x800000) {
		temp |= (-0x800000);
	}
	return temp;
}