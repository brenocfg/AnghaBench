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

__attribute__((used)) static int
parse_integer(const char *str)
{
	static const int RADIX = 10;  /* XXXJA: possibly support hex? */
	const char *orig;
	int n;
	char c;

	orig = str;
	n = 0;
	for (c = *str; c != '\0'; c = *++str) {
		if (c < '0' || c > '9')
			return (-1);

		n *= RADIX;
		n += c - '0';
	}

	/* Make sure we actually parsed something. */
	if (str == orig)
		return (-1);
	return (n);
}