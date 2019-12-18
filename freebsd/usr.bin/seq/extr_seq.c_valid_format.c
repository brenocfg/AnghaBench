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
 scalar_t__ strchr (char*,char const) ; 

__attribute__((used)) static int
valid_format(const char *fmt)
{
	unsigned conversions = 0;

	while (*fmt != '\0') {
		/* scan for conversions */
		if (*fmt != '%') {
			fmt++;
			continue;
		}
		fmt++;

		/* allow %% but not things like %10% */
		if (*fmt == '%') {
			fmt++;
			continue;
		}

		/* flags */
		while (*fmt != '\0' && strchr("#0- +'", *fmt)) {
			fmt++;
		}

		/* field width */
		while (*fmt != '\0' && strchr("0123456789", *fmt)) {
			fmt++;
		}

		/* precision */
		if (*fmt == '.') {
			fmt++;
			while (*fmt != '\0' && strchr("0123456789", *fmt)) {
				fmt++;
			}
		}

		/* conversion */
		switch (*fmt) {
		    case 'A':
		    case 'a':
		    case 'E':
		    case 'e':
		    case 'F':
		    case 'f':
		    case 'G':
		    case 'g':
			/* floating point formats are accepted */
			conversions++;
			break;
		    default:
			/* anything else is not */
			return 0;
		}
	}

	/* PR 236347 -- user format strings must have a conversion */
	return (conversions == 1);
}