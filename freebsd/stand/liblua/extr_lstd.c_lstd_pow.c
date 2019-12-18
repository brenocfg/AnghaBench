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
typedef  scalar_t__ int64_t ;

/* Variables and functions */

int64_t
lstd_pow(int64_t x, int64_t y)
{
	int64_t rv = 1;

	if (y < 0)
		return 0;
	rv = x;
	while (--y)
		rv *= x;

	return rv;
}