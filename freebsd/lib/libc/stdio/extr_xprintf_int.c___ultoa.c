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
typedef  int u_long ;

/* Variables and functions */
 char const CHAR_MAX ; 
 int LONG_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 char to_char (int) ; 

__attribute__((used)) static char *
__ultoa(u_long val, char *endp, int base, const char *xdigs,
	int needgrp, char thousep, const char *grp)
{
	char *cp = endp;
	long sval;
	int ndig;

	/*
	 * Handle the three cases separately, in the hope of getting
	 * better/faster code.
	 */
	switch (base) {
	case 10:
		if (val < 10) {	/* many numbers are 1 digit */
			*--cp = to_char(val);
			return (cp);
		}
		ndig = 0;
		/*
		 * On many machines, unsigned arithmetic is harder than
		 * signed arithmetic, so we do at most one unsigned mod and
		 * divide; this is sufficient to reduce the range of
		 * the incoming value to where signed arithmetic works.
		 */
		if (val > LONG_MAX) {
			*--cp = to_char(val % 10);
			ndig++;
			sval = val / 10;
		} else
			sval = val;
		do {
			*--cp = to_char(sval % 10);
			ndig++;
			/*
			 * If (*grp == CHAR_MAX) then no more grouping
			 * should be performed.
			 */
			if (needgrp && ndig == *grp && *grp != CHAR_MAX
					&& sval > 9) {
				*--cp = thousep;
				ndig = 0;
				/*
				 * If (*(grp+1) == '\0') then we have to
				 * use *grp character (last grouping rule)
				 * for all next cases
				 */
				if (*(grp+1) != '\0')
					grp++;
			}
			sval /= 10;
		} while (sval != 0);
		break;

	case 8:
		do {
			*--cp = to_char(val & 7);
			val >>= 3;
		} while (val);
		break;

	case 16:
		do {
			*--cp = xdigs[val & 15];
			val >>= 4;
		} while (val);
		break;

	default:			/* oops */
		assert(base == 16);
	}
	return (cp);
}