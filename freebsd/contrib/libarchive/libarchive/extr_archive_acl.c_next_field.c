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

__attribute__((used)) static void
next_field(const char **p, const char **start,
    const char **end, char *sep)
{
	/* Skip leading whitespace to find start of field. */
	while (**p == ' ' || **p == '\t' || **p == '\n') {
		(*p)++;
	}
	*start = *p;

	/* Scan for the separator. */
	while (**p != '\0' && **p != ',' && **p != ':' && **p != '\n' &&
	    **p != '#') {
		(*p)++;
	}
	*sep = **p;

	/* Locate end of field, trim trailing whitespace if necessary */
	if (*p == *start) {
		*end = *p;
	} else {
		*end = *p - 1;
		while (**end == ' ' || **end == '\t' || **end == '\n') {
			(*end)--;
		}
		(*end)++;
	}

	/* Handle in-field comments */
	if (*sep == '#') {
		while (**p != '\0' && **p != ',' && **p != '\n') {
			(*p)++;
		}
		*sep = **p;
	}

	/* Adjust scanner location. */
	if (**p != '\0')
		(*p)++;
}