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
 int INT64_MAX ; 
 int INT64_MIN ; 
 int parsedigit (char) ; 

__attribute__((used)) static int64_t
mtree_atol(char **p, int base)
{
	int64_t l, limit;
	int digit, last_digit_limit;

	if (base == 0) {
		if (**p != '0')
			base = 10;
		else if ((*p)[1] == 'x' || (*p)[1] == 'X') {
			*p += 2;
			base = 16;
		} else {
			base = 8;
		}
	}

	if (**p == '-') {
		limit = INT64_MIN / base;
		last_digit_limit = INT64_MIN % base;
		++(*p);

		l = 0;
		digit = parsedigit(**p);
		while (digit >= 0 && digit < base) {
			if (l < limit || (l == limit && digit > last_digit_limit))
				return INT64_MIN;
			l = (l * base) - digit;
			digit = parsedigit(*++(*p));
		}
		return l;
	} else {
		limit = INT64_MAX / base;
		last_digit_limit = INT64_MAX % base;

		l = 0;
		digit = parsedigit(**p);
		while (digit >= 0 && digit < base) {
			if (l > limit || (l == limit && digit > last_digit_limit))
				return INT64_MAX;
			l = (l * base) + digit;
			digit = parsedigit(*++(*p));
		}
		return l;
	}
}