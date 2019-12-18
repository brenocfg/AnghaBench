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
pm_list(const char *start, const char *end, const char c, int flags)
{
	const char *p = start;
	char rangeStart = '\0', nextRangeStart;
	int match = 1, nomatch = 0;

	/* This will be used soon... */
	(void)flags; /* UNUSED */

	/* If this is a negated class, return success for nomatch. */
	if ((*p == '!' || *p == '^') && p < end) {
		match = 0;
		nomatch = 1;
		++p;
	}

	while (p < end) {
		nextRangeStart = '\0';
		switch (*p) {
		case '-':
			/* Trailing or initial '-' is not special. */
			if ((rangeStart == '\0') || (p == end - 1)) {
				if (*p == c)
					return (match);
			} else {
				char rangeEnd = *++p;
				if (rangeEnd == '\\')
					rangeEnd = *++p;
				if ((rangeStart <= c) && (c <= rangeEnd))
					return (match);
			}
			break;
		case '\\':
			++p;
			/* Fall through */
		default:
			if (*p == c)
				return (match);
			nextRangeStart = *p; /* Possible start of range. */
		}
		rangeStart = nextRangeStart;
		++p;
	}
	return (nomatch);
}