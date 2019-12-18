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
portcompare(char * a, char * b)
{
	size_t i;

	/* Find first non-matching position */
	for (i = 0; ; i++) {
		if (a[i] != b[i])
			break;
		if (a[i] == 0)			/* End of strings */
			return 0;
	}

	/* One string is a prefix of the other */
	if (a[i] == 0)
		return -1;
	if (b[i] == 0)
		return 1;

	/* One string has a category which is a prefix of the other */
	if (a[i] == '/')
		return -1;
	if (b[i] == '/')
		return 1;

	/* The two strings are simply different */
	if (a[i] < b[i])
		return -1;
	else
		return 1;
}