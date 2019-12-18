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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

uint32_t
msb64(uint64_t x)
{
	uint64_t m = 1ULL << 63;
	int i;

	for (i = 63; i >= 0; i--, m >>=1)
		if (m & x)
			return i;
	return 0;
}