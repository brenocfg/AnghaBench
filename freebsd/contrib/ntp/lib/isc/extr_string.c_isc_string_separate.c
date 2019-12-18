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

char *
isc_string_separate(char **stringp, const char *delim) {
	char *string = *stringp;
	char *s;
	const char *d;
	char sc, dc;

	if (string == NULL)
		return (NULL);

	for (s = string; (sc = *s) != '\0'; s++)
		for (d = delim; (dc = *d) != '\0'; d++)
			if (sc == dc) {
				*s++ = '\0';
				*stringp = s;
				return (string);
			}
	*stringp = NULL;
	return (string);
}