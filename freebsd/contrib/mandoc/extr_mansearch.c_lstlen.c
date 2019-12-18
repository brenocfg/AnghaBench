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

__attribute__((used)) static size_t
lstlen(const char *cp, size_t sep)
{
	size_t	 sz;

	for (sz = 0; *cp != '\0'; cp++) {

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
		if (sz)
			sz += sep;

		/* Copy one string. */
		while (*cp != '\0') {
			sz++;
			cp++;
		}
	}
	return sz;
}