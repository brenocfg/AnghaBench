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
typedef  int uint64_t ;
typedef  int off_t ;

/* Variables and functions */

off_t
gv_sizespec(char *spec)
{
	uint64_t size;
	char *s;
	int sign;
	
	size = 0;
	sign = 1;
	if (spec != NULL) {		/* we have a parameter */
		s = spec;
		if (*s == '-') {	/* negative, */
			sign = -1;
			s++;		/* skip */
		}

		/* It's numeric. */
		if ((*s >= '0') && (*s <= '9')) {

			/* It's numeric. */
			while ((*s >= '0') && (*s <= '9'))
				/* Convert it. */
				size = size * 10 + *s++ - '0';

			switch (*s) {
			case '\0':
				return size * sign;
			
			case 'B':
			case 'b':
			case 'S':
			case 's':
				return size * sign * 512;
			
			case 'K':
			case 'k':
				return size * sign * 1024;
			
			case 'M':
			case 'm':
				return size * sign * 1024 * 1024;
			
			case 'G':
			case 'g':
				return size * sign * 1024 * 1024 * 1024;
			}
		}
	}

	return (0);
}