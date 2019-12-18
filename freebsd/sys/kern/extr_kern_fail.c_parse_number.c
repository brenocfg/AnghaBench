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
 int PROB_DIGITS ; 
 scalar_t__ isdigit (char) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static char *
parse_number(int *out_units, int *out_decimal, char *p)
{
	char *old_p;

	/**
	 *  <number> ::
	 *      <integer> [ "." <integer> ] |
	 *      "." <integer>
	 */

	/* whole part */
	old_p = p;
	*out_units = strtol(p, &p, 10);
	if (p == old_p && *p != '.')
		return (NULL);

	/* fractional part */
	*out_decimal = 0;
	if (*p == '.') {
		int digits = 0;
		p++;
		while (isdigit(*p)) {
			int digit = *p - '0';
			if (digits < PROB_DIGITS - 2)
				*out_decimal = *out_decimal * 10 + digit;
			else if (digits == PROB_DIGITS - 2 && digit >= 5)
				(*out_decimal)++;
			digits++;
			p++;
		}
		if (!digits) /* need at least one digit after '.' */
			return (NULL);
		while (digits++ < PROB_DIGITS - 2) /* add implicit zeros */
			*out_decimal *= 10;
	}

	return (p); /* success */
}