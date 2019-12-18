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
typedef  int u_int ;

/* Variables and functions */
 scalar_t__ bhnd_nv_isdigit (char) ; 
 scalar_t__ bhnd_nv_isupper (char) ; 
 scalar_t__ bhnd_nv_isxdigit (char) ; 

__attribute__((used)) static bool
bhnd_nvram_ident_num_string(const char *inp, size_t ilen, u_int base,
    u_int *obase)
{
	size_t	nbytes, ndigits;

	nbytes = 0;
	ndigits = 0;

	/* Parse and skip sign */
	if (nbytes >= ilen)
		return (false);

	if (inp[nbytes] == '-' || inp[nbytes] == '+')
		nbytes++;

	/* Truncated after sign character? */
	if (nbytes == ilen)
		return (false);

	/* Identify (or validate) hex base, skipping 0x/0X prefix */
	if (base == 16 || base == 0) {
		/* Check for (and skip) 0x/0X prefix */
		if (ilen - nbytes >= 2 && inp[nbytes] == '0' &&
		    (inp[nbytes+1] == 'x' || inp[nbytes+1] == 'X'))
		{
			base = 16;
			nbytes += 2;
		}
	}

	/* Truncated after hex prefix? */
	if (nbytes == ilen)
		return (false);

	/* Differentiate decimal/octal by looking for a leading 0 */
	if (base == 0) {
		if (inp[nbytes] == '0') {
			base = 8;
		} else {
			base = 10;
		}
	}

	/* Consume and validate all remaining digit characters */
	for (; nbytes < ilen; nbytes++) {
		u_int	carry;
		char	c;

		/* Parse carry value */
		c = inp[nbytes];
		if (bhnd_nv_isdigit(c)) {
			carry = c - '0';
		} else if (bhnd_nv_isxdigit(c)) {
			if (bhnd_nv_isupper(c))
				carry = (c - 'A') + 10;
			else
				carry = (c - 'a') + 10;
		} else {
			/* Hit a non-digit character */
			return (false);
		}

		/* If carry is outside the base, it's not a valid digit
		 * in the current parse context; consider it a non-digit
		 * character */
		if (carry >= base)
			return (false);

		/* Increment parsed digit count */
		ndigits++;
	}

	/* Empty integer string? */
	if (ndigits == 0)
		return (false);

	/* Valid integer -- provide the base and return */
	if (obase != NULL)
		*obase = base;
	return (true);
}