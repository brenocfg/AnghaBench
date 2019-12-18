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
 unsigned int PATTERN_FLAG_ENDSWITH ; 
 scalar_t__ fnmatch_icase_mem (char const*,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fspathncmp (char const*,char const*,int) ; 

int match_basename(const char *basename, int basenamelen,
		   const char *pattern, int prefix, int patternlen,
		   unsigned flags)
{
	if (prefix == patternlen) {
		if (patternlen == basenamelen &&
		    !fspathncmp(pattern, basename, basenamelen))
			return 1;
	} else if (flags & PATTERN_FLAG_ENDSWITH) {
		/* "*literal" matching against "fooliteral" */
		if (patternlen - 1 <= basenamelen &&
		    !fspathncmp(pattern + 1,
				   basename + basenamelen - (patternlen - 1),
				   patternlen - 1))
			return 1;
	} else {
		if (fnmatch_icase_mem(pattern, patternlen,
				      basename, basenamelen,
				      0) == 0)
			return 1;
	}
	return 0;
}