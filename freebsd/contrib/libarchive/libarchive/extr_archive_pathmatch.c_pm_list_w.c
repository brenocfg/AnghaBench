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
typedef  int wchar_t ;

/* Variables and functions */

__attribute__((used)) static int
pm_list_w(const wchar_t *start, const wchar_t *end, const wchar_t c, int flags)
{
	const wchar_t *p = start;
	wchar_t rangeStart = L'\0', nextRangeStart;
	int match = 1, nomatch = 0;

	/* This will be used soon... */
	(void)flags; /* UNUSED */

	/* If this is a negated class, return success for nomatch. */
	if ((*p == L'!' || *p == L'^') && p < end) {
		match = 0;
		nomatch = 1;
		++p;
	}

	while (p < end) {
		nextRangeStart = L'\0';
		switch (*p) {
		case L'-':
			/* Trailing or initial '-' is not special. */
			if ((rangeStart == L'\0') || (p == end - 1)) {
				if (*p == c)
					return (match);
			} else {
				wchar_t rangeEnd = *++p;
				if (rangeEnd == L'\\')
					rangeEnd = *++p;
				if ((rangeStart <= c) && (c <= rangeEnd))
					return (match);
			}
			break;
		case L'\\':
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