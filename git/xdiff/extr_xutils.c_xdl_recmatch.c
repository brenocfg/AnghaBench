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
 long XDF_IGNORE_CR_AT_EOL ; 
 long XDF_IGNORE_WHITESPACE ; 
 long XDF_IGNORE_WHITESPACE_AT_EOL ; 
 long XDF_IGNORE_WHITESPACE_CHANGE ; 
 long XDF_WHITESPACE_FLAGS ; 
 scalar_t__ XDL_ISSPACE (char const) ; 
 scalar_t__ ends_with_optional_cr (char const*,long,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,long) ; 

int xdl_recmatch(const char *l1, long s1, const char *l2, long s2, long flags)
{
	int i1, i2;

	if (s1 == s2 && !memcmp(l1, l2, s1))
		return 1;
	if (!(flags & XDF_WHITESPACE_FLAGS))
		return 0;

	i1 = 0;
	i2 = 0;

	/*
	 * -w matches everything that matches with -b, and -b in turn
	 * matches everything that matches with --ignore-space-at-eol,
	 * which in turn matches everything that matches with --ignore-cr-at-eol.
	 *
	 * Each flavor of ignoring needs different logic to skip whitespaces
	 * while we have both sides to compare.
	 */
	if (flags & XDF_IGNORE_WHITESPACE) {
		goto skip_ws;
		while (i1 < s1 && i2 < s2) {
			if (l1[i1++] != l2[i2++])
				return 0;
		skip_ws:
			while (i1 < s1 && XDL_ISSPACE(l1[i1]))
				i1++;
			while (i2 < s2 && XDL_ISSPACE(l2[i2]))
				i2++;
		}
	} else if (flags & XDF_IGNORE_WHITESPACE_CHANGE) {
		while (i1 < s1 && i2 < s2) {
			if (XDL_ISSPACE(l1[i1]) && XDL_ISSPACE(l2[i2])) {
				/* Skip matching spaces and try again */
				while (i1 < s1 && XDL_ISSPACE(l1[i1]))
					i1++;
				while (i2 < s2 && XDL_ISSPACE(l2[i2]))
					i2++;
				continue;
			}
			if (l1[i1++] != l2[i2++])
				return 0;
		}
	} else if (flags & XDF_IGNORE_WHITESPACE_AT_EOL) {
		while (i1 < s1 && i2 < s2 && l1[i1] == l2[i2]) {
			i1++;
			i2++;
		}
	} else if (flags & XDF_IGNORE_CR_AT_EOL) {
		/* Find the first difference and see how the line ends */
		while (i1 < s1 && i2 < s2 && l1[i1] == l2[i2]) {
			i1++;
			i2++;
		}
		return (ends_with_optional_cr(l1, s1, i1) &&
			ends_with_optional_cr(l2, s2, i2));
	}

	/*
	 * After running out of one side, the remaining side must have
	 * nothing but whitespace for the lines to match.  Note that
	 * ignore-whitespace-at-eol case may break out of the loop
	 * while there still are characters remaining on both lines.
	 */
	if (i1 < s1) {
		while (i1 < s1 && XDL_ISSPACE(l1[i1]))
			i1++;
		if (s1 != i1)
			return 0;
	}
	if (i2 < s2) {
		while (i2 < s2 && XDL_ISSPACE(l2[i2]))
			i2++;
		return (s2 == i2);
	}
	return 1;
}