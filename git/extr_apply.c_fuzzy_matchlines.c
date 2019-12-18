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
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static int fuzzy_matchlines(const char *s1, size_t n1,
			    const char *s2, size_t n2)
{
	const char *end1 = s1 + n1;
	const char *end2 = s2 + n2;

	/* ignore line endings */
	while (s1 < end1 && (end1[-1] == '\r' || end1[-1] == '\n'))
		end1--;
	while (s2 < end2 && (end2[-1] == '\r' || end2[-1] == '\n'))
		end2--;

	while (s1 < end1 && s2 < end2) {
		if (isspace(*s1)) {
			/*
			 * Skip whitespace. We check on both buffers
			 * because we don't want "a b" to match "ab".
			 */
			if (!isspace(*s2))
				return 0;
			while (s1 < end1 && isspace(*s1))
				s1++;
			while (s2 < end2 && isspace(*s2))
				s2++;
		} else if (*s1++ != *s2++)
			return 0;
	}

	/* If we reached the end on one side only, lines don't match. */
	return s1 == end1 && s2 == end2;
}