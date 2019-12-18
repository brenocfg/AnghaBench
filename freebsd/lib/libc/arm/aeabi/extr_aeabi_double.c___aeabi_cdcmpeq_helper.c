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
typedef  int float64 ;

/* Variables and functions */

int
__aeabi_cdcmpeq_helper(float64 a, float64 b)
{
	int quiet = 0;

	/* Check if a is a NaN */
	if ((a << 1) > 0xffe0000000000000ull) {
		/* If it's a signalling NaN we will always signal */
		if ((a & 0x0008000000000000ull) == 0)
			return (0);

		quiet = 1;
	}

	/* Check if b is a NaN */
	if ((b << 1) > 0xffe0000000000000ull) {
		/* If it's a signalling NaN we will always signal */
		if ((b & 0x0008000000000000ull) == 0)
			return (0);

		quiet = 1;
	}

	return (quiet);
}