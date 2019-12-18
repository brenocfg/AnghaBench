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
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int INT64_MAX ; 
 int INT64_MIN ; 
 scalar_t__ git__isspace (char const) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git__strntol64(int64_t *result, const char *nptr, size_t nptr_len, const char **endptr, int base)
{
	const char *p;
	int64_t n, nn;
	int c, ovfl, v, neg, ndig;

	p = nptr;
	neg = 0;
	n = 0;
	ndig = 0;
	ovfl = 0;

	/*
	 * White space
	 */
	while (nptr_len && git__isspace(*p))
		p++, nptr_len--;

	if (!nptr_len)
		goto Return;

	/*
	 * Sign
	 */
	if (*p == '-' || *p == '+') {
		if (*p == '-')
			neg = 1;
		p++;
		nptr_len--;
	}

	if (!nptr_len)
		goto Return;

	/*
	 * Automatically detect the base if none was given to us.
	 * Right now, we assume that a number starting with '0x'
	 * is hexadecimal and a number starting with '0' is
	 * octal.
	 */
	if (base == 0) {
		if (*p != '0')
			base = 10;
		else if (nptr_len > 2 && (p[1] == 'x' || p[1] == 'X'))
			base = 16;
		else
			base = 8;
	}

	if (base < 0 || 36 < base)
		goto Return;

	/*
	 * Skip prefix of '0x'-prefixed hexadecimal numbers. There is no
	 * need to do the same for '0'-prefixed octal numbers as a
	 * leading '0' does not have any impact. Also, if we skip a
	 * leading '0' in such a string, then we may end up with no
	 * digits left and produce an error later on which isn't one.
	 */
	if (base == 16 && nptr_len > 2 && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
		p += 2;
		nptr_len -= 2;
	}

	/*
	 * Non-empty sequence of digits
	 */
	for (; nptr_len > 0; p++,ndig++,nptr_len--) {
		c = *p;
		v = base;
		if ('0'<=c && c<='9')
			v = c - '0';
		else if ('a'<=c && c<='z')
			v = c - 'a' + 10;
		else if ('A'<=c && c<='Z')
			v = c - 'A' + 10;
		if (v >= base)
			break;
		v = neg ? -v : v;
		if (n > INT64_MAX / base || n < INT64_MIN / base) {
			ovfl = 1;
			/* Keep on iterating until the end of this number */
			continue;
		}
		nn = n * base;
		if ((v > 0 && nn > INT64_MAX - v) ||
		    (v < 0 && nn < INT64_MIN - v)) {
			ovfl = 1;
			/* Keep on iterating until the end of this number */
			continue;
		}
		n = nn + v;
	}

Return:
	if (ndig == 0) {
		git_error_set(GIT_ERROR_INVALID, "failed to convert string to long: not a number");
		return -1;
	}

	if (endptr)
		*endptr = p;

	if (ovfl) {
		git_error_set(GIT_ERROR_INVALID, "failed to convert string to long: overflow error");
		return -1;
	}

	*result = n;
	return 0;
}