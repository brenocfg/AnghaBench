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

__attribute__((used)) static int sqrti(int val)
{
	float d, x = val;

	if (val == 0)
		return 0;

	do {
		float y = (x + (float)val / x) / 2;
		d = (y > x) ? y - x : x - y;
		x = y;
	} while (d >= 0.5);

	return (int)x;
}