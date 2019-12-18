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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int LLONG_MAX ; 
 long long LLONG_MIN ; 
 int MAX_DIGITS ; 
 unsigned int SCALE_LENGTH ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 char* scale_chars ; 
 long long* scale_factors ; 
 char tolower (unsigned char) ; 

int
scan_scaled(char *scaled, long long *result)
{
	char *p = scaled;
	int sign = 0;
	unsigned int i, ndigits = 0, fract_digits = 0;
	long long scale_fact = 1, whole = 0, fpart = 0;

	/* Skip leading whitespace */
	while (isascii((unsigned char)*p) && isspace((unsigned char)*p))
		++p;

	/* Then at most one leading + or - */
	while (*p == '-' || *p == '+') {
		if (*p == '-') {
			if (sign) {
				errno = EINVAL;
				return -1;
			}
			sign = -1;
			++p;
		} else if (*p == '+') {
			if (sign) {
				errno = EINVAL;
				return -1;
			}
			sign = +1;
			++p;
		}
	}

	/* Main loop: Scan digits, find decimal point, if present.
	 * We don't allow exponentials, so no scientific notation
	 * (but note that E for Exa might look like e to some!).
	 * Advance 'p' to end, to get scale factor.
	 */
	for (; isascii((unsigned char)*p) &&
	    (isdigit((unsigned char)*p) || *p=='.'); ++p) {
		if (*p == '.') {
			if (fract_digits > 0) {	/* oops, more than one '.' */
				errno = EINVAL;
				return -1;
			}
			fract_digits = 1;
			continue;
		}

		i = (*p) - '0';			/* whew! finally a digit we can use */
		if (fract_digits > 0) {
			if (fract_digits >= MAX_DIGITS-1)
				/* ignore extra fractional digits */
				continue;
			fract_digits++;		/* for later scaling */
			if (fpart > LLONG_MAX / 10) {
				errno = ERANGE;
				return -1;
			}
			fpart *= 10;
			if (i > LLONG_MAX - fpart) {
				errno = ERANGE;
				return -1;
			}
			fpart += i;
		} else {				/* normal digit */
			if (++ndigits >= MAX_DIGITS) {
				errno = ERANGE;
				return -1;
			}
			if (whole > LLONG_MAX / 10) {
				errno = ERANGE;
				return -1;
			}
			whole *= 10;
			if (i > LLONG_MAX - whole) {
				errno = ERANGE;
				return -1;
			}
			whole += i;
		}
	}

	if (sign) {
		whole *= sign;
		fpart *= sign;
	}

	/* If no scale factor given, we're done. fraction is discarded. */
	if (!*p) {
		*result = whole;
		return 0;
	}

	/* Validate scale factor, and scale whole and fraction by it. */
	for (i = 0; i < SCALE_LENGTH; i++) {

		/* Are we there yet? */
		if (*p == scale_chars[i] ||
			*p == tolower((unsigned char)scale_chars[i])) {

			/* If it ends with alphanumerics after the scale char, bad. */
			if (isalnum((unsigned char)*(p+1))) {
				errno = EINVAL;
				return -1;
			}
			scale_fact = scale_factors[i];

			/* check for overflow and underflow after scaling */
			if (whole > LLONG_MAX / scale_fact ||
			    whole < LLONG_MIN / scale_fact) {
				errno = ERANGE;
				return -1;
			}

			/* scale whole part */
			whole *= scale_fact;

			/* truncate fpart so it doesn't overflow.
			 * then scale fractional part.
			 */
			while (fpart >= LLONG_MAX / scale_fact) {
				fpart /= 10;
				fract_digits--;
			}
			fpart *= scale_fact;
			if (fract_digits > 0) {
				for (i = 0; i < fract_digits -1; i++)
					fpart /= 10;
			}
			whole += fpart;
			*result = whole;
			return 0;
		}
	}

	/* Invalid unit or character */
	errno = EINVAL;
	return -1;
}