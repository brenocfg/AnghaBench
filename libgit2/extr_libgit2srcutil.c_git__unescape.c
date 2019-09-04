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

size_t git__unescape(char *str)
{
	char *scan, *pos = str;

	if (!str)
		return 0;

	for (scan = str; *scan; pos++, scan++) {
		if (*scan == '\\' && *(scan + 1) != '\0')
			scan++; /* skip '\' but include next char */
		if (pos != scan)
			*pos = *scan;
	}

	if (pos != scan) {
		*pos = '\0';
	}

	return (pos - str);
}