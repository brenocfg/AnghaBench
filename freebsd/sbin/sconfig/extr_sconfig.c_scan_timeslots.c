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
 long strtol (char*,char**,int) ; 

__attribute__((used)) static unsigned long
scan_timeslots (char *s)
{
	char *e;
	long v;
	int i;
	unsigned long ts, lastv;

	ts = lastv = 0;
	for (;;) {
		v = strtol (s, &e, 10);
		if (e == s)
			break;
		if (*e == '-') {
			lastv = v;
			s = e+1;
			continue;
		}
		if (*e == ',')
			++e;

		if (lastv)
			for (i=lastv; i<v; ++i)
				ts |= 1L << i;
		ts |= 1L << v;

		lastv = 0;
		s = e;
	}
	return ts;
}