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

__attribute__((used)) static size_t trailing_space_length(const char *p, size_t len)
{
	size_t n, i;
	for (n = len; n; n--) {
		if (p[n-1] != ' ' && p[n-1] != '\t')
			break;

		/*
		 * Count escape-characters before space. In case where it's an
		 * even number of escape characters, then the escape char itself
		 * is escaped and the whitespace is an unescaped whitespace.
		 * Otherwise, the last escape char is not escaped and the
		 * whitespace in an escaped whitespace.
		 */
		i = n;
		while (i > 1 && p[i-2] == '\\')
			i--;
		if ((n - i) % 2)
			break;
	}
	return len - n;
}