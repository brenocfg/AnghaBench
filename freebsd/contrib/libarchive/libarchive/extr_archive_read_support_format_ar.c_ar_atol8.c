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
typedef  unsigned int uint64_t ;

/* Variables and functions */
 unsigned int UINT64_MAX ; 

__attribute__((used)) static uint64_t
ar_atol8(const char *p, unsigned char_cnt)
{
	uint64_t l, limit, last_digit_limit;
	unsigned int digit, base;

	base = 8;
	limit = UINT64_MAX / base;
	last_digit_limit = UINT64_MAX % base;

	while ((*p == ' ' || *p == '\t') && char_cnt-- > 0)
		p++;

	l = 0;
	digit = *p - '0';
	while (*p >= '0' && digit < base  && char_cnt-- > 0) {
		if (l>limit || (l == limit && digit > last_digit_limit)) {
			l = UINT64_MAX; /* Truncate on overflow. */
			break;
		}
		l = (l * base) + digit;
		digit = *++p - '0';
	}
	return (l);
}