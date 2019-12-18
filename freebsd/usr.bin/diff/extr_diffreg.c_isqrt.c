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

/* Variables and functions */

__attribute__((used)) static int
isqrt(int n)
{
	int y, x = 1;

	if (n == 0)
		return (0);

	do { /* newton was a stinker */
		y = x;
		x = n / x;
		x += y;
		x /= 2;
	} while ((x - y) > 1 || (x - y) < -1);

	return (x);
}