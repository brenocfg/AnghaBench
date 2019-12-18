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

__attribute__((used)) static void mult64(unsigned long long x, unsigned long long y,
		unsigned long long *highp, unsigned long long *lowp)
{
	unsigned long long sub0, sub1, sub2, sub3;
	unsigned long long high, low;

	sub0 = (x >> 32) * (unsigned long) (y >> 32);
	sub1 = (x & 0xffffffffLL) * (unsigned long) (y >> 32);
	sub2 = (x >> 32) * (unsigned long) (y & 0xffffffffLL);
	sub3 = (x & 0xffffffffLL) * (unsigned long) (y & 0xffffffffLL);
	low = sub3;
	high = 0LL;
	sub3 += (sub1 << 32);
	if (low > sub3)
		high++;
	low = sub3;
	sub3 += (sub2 << 32);
	if (low > sub3)
		high++;
	low = sub3;
	high += (sub1 >> 32) + (sub2 >> 32);
	high += sub0;
	*lowp = low;
	*highp = high;
}