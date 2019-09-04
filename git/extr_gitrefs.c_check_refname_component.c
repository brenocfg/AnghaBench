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
 int /*<<< orphan*/  LOCK_SUFFIX ; 
 int LOCK_SUFFIX_LEN ; 
 int REFNAME_REFSPEC_PATTERN ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 unsigned char* refname_disposition ; 

__attribute__((used)) static int check_refname_component(const char *refname, int *flags)
{
	const char *cp;
	char last = '\0';

	for (cp = refname; ; cp++) {
		int ch = *cp & 255;
		unsigned char disp = refname_disposition[ch];
		switch (disp) {
		case 1:
			goto out;
		case 2:
			if (last == '.')
				return -1; /* Refname contains "..". */
			break;
		case 3:
			if (last == '@')
				return -1; /* Refname contains "@{". */
			break;
		case 4:
			return -1;
		case 5:
			if (!(*flags & REFNAME_REFSPEC_PATTERN))
				return -1; /* refspec can't be a pattern */

			/*
			 * Unset the pattern flag so that we only accept
			 * a single asterisk for one side of refspec.
			 */
			*flags &= ~ REFNAME_REFSPEC_PATTERN;
			break;
		}
		last = ch;
	}
out:
	if (cp == refname)
		return 0; /* Component has zero length. */
	if (refname[0] == '.')
		return -1; /* Component starts with '.'. */
	if (cp - refname >= LOCK_SUFFIX_LEN &&
	    !memcmp(cp - LOCK_SUFFIX_LEN, LOCK_SUFFIX, LOCK_SUFFIX_LEN))
		return -1; /* Refname ends with ".lock". */
	return cp - refname;
}