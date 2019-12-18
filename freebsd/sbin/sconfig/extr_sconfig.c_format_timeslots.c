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

__attribute__((used)) static char *
format_timeslots (unsigned long s)
{
	static char buf [100];
	char *p = buf;
	int i;

	for (i=1; i<32; ++i)
		if ((s >> i) & 1) {
			int prev = (i > 1)  & (s >> (i-1));
			int next = (i < 31) & (s >> (i+1));

			if (prev) {
				if (next)
					continue;
				*p++ = '-';
			} else if (p > buf)
				*p++ = ',';

			if (i >= 10)
				*p++ = '0' + i / 10;
			*p++ = '0' + i % 10;
		}
	*p = 0;
	return buf;
}