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
 scalar_t__ malloc (int) ; 

__attribute__((used)) static char *fixregex(char *s)
{
	int len = 0;
	int esc_count = 0;
	char *fixed = NULL;
	char *p, *q;

	/* Count the number of '\' in string */
	for (p = s; *p; p++) {
		++len;
		if (*p == '\\')
			++esc_count;
	}

	if (esc_count == 0)
		return s;

	/* allocate space for a new string */
	fixed = (char *) malloc(len + 1);
	if (!fixed)
		return NULL;

	/* copy over the characters */
	q = fixed;
	for (p = s; *p; p++) {
		if (*p == '\\') {
			*q = '\\';
			++q;
		}
		*q = *p;
		++q;
	}
	*q = '\0';
	return fixed;
}