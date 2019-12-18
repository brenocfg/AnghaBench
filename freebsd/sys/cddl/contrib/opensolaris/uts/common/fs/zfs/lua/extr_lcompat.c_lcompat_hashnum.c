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
typedef  int int64_t ;

/* Variables and functions */

int
lcompat_hashnum(int64_t x)
{
	x = (~x) + (x << 18);
	x = x ^ (x >> 31);
	x = x * 21;
	x = x ^ (x >> 11);
	x = x + (x << 6);
	x = x ^ (x >> 22);
	return ((int)x);
}