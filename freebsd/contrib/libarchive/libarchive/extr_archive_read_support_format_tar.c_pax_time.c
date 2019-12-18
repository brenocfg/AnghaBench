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
typedef  char int64_t ;

/* Variables and functions */
 int INT64_MAX ; 

__attribute__((used)) static void
pax_time(const char *p, int64_t *ps, long *pn)
{
	char digit;
	int64_t	s;
	unsigned long l;
	int sign;
	int64_t limit, last_digit_limit;

	limit = INT64_MAX / 10;
	last_digit_limit = INT64_MAX % 10;

	s = 0;
	sign = 1;
	if (*p == '-') {
		sign = -1;
		p++;
	}
	while (*p >= '0' && *p <= '9') {
		digit = *p - '0';
		if (s > limit ||
		    (s == limit && digit > last_digit_limit)) {
			s = INT64_MAX;
			break;
		}
		s = (s * 10) + digit;
		++p;
	}

	*ps = s * sign;

	/* Calculate nanoseconds. */
	*pn = 0;

	if (*p != '.')
		return;

	l = 100000000UL;
	do {
		++p;
		if (*p >= '0' && *p <= '9')
			*pn += (*p - '0') * l;
		else
			break;
	} while (l /= 10);
}