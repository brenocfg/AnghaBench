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
 int NAME_MASK ; 
 int NAME_SYN ; 

__attribute__((used)) static void
lstcat(char *buf, size_t *i, const char *cp, const char *sep)
{
	const char	*s;
	size_t		 i_start;

	for (i_start = *i; *cp != '\0'; cp++) {

		/* Skip names appearing only in the SYNOPSIS. */
		if (*cp <= (char)(NAME_SYN & NAME_MASK)) {
			while (*cp != '\0')
				cp++;
			continue;
		}

		/* Skip name class markers. */
		if (*cp < ' ')
			cp++;

		/* Print a separator before each but the first string. */
		if (*i > i_start) {
			s = sep;
			while (*s != '\0')
				buf[(*i)++] = *s++;
		}

		/* Copy one string. */
		while (*cp != '\0')
			buf[(*i)++] = *cp++;
	}

}