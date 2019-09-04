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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ git__tolower (char const) ; 

int git__strcasesort_cmp(const char *a, const char *b)
{
	int cmp = 0;

	while (*a && *b) {
		if (*a != *b) {
			if (git__tolower(*a) != git__tolower(*b))
				break;
			/* use case in sort order even if not in equivalence */
			if (!cmp)
				cmp = (int)(*(const uint8_t *)a) - (int)(*(const uint8_t *)b);
		}

		++a, ++b;
	}

	if (*a || *b)
		return (unsigned char)git__tolower(*a) - (unsigned char)git__tolower(*b);

	return cmp;
}