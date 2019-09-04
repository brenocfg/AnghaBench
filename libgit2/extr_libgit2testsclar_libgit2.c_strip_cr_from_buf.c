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

__attribute__((used)) static size_t strip_cr_from_buf(char *start, size_t len)
{
	char *scan, *trail, *end = start + len;

	for (scan = trail = start; scan < end; trail++, scan++) {
		while (*scan == '\r')
			scan++; /* skip '\r' */

		if (trail != scan)
			*trail = *scan;
	}

	*trail = '\0';

	return (trail - start);
}