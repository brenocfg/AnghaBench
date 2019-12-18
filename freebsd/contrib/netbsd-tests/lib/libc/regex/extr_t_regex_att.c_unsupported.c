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
 size_t __arraycount (char const**) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int
unsupported(const char *s)
{
	static const char *we[] = {
#if defined(REGEX_SPENCER)
		"ASSOCIATIVITY=left",		// have right associativity
		"SUBEXPRESSION=precedence",	// have grouping subexpression
		"REPEAT_LONGEST=last",		// have first repeat longest
		"BUG=alternation-order",	// don't have it
		"BUG=first-match",		// don't have it
		"BUG=nomatch-match",		// don't have it
		"BUG=repeat-any",		// don't have it
		"BUG=range-null",		// don't have it
		"BUG=repeat-null-unknown",	// don't have it
		"BUG=repeat-null",		// don't have it
		"BUG=repeat-artifact",		// don't have it
		"BUG=subexpression-first",	// don't have it
#elif defined(REGEX_TRE)
		"ASSOCIATIVITY=right",		// have left associativity
		"SUBEXPRESSION=grouping",	// have precedence subexpression
		"REPEAT_LONGEST=first",		// have last repeat longest
		"LENGTH=first",			// have last length
		"BUG=alternation-order",	// don't have it
		"BUG=first-match",		// don't have it
		"BUG=range-null",		// don't have it
		"BUG=repeat-null",		// don't have it
		"BUG=repeat-artifact",		// don't have it
		"BUG=subexpression-first",	// don't have it
		"BUG=repeat-short",		// don't have it
#endif
	};

	if (s == NULL)
		return 0;

	while (*s == '#' || isspace((unsigned char)*s))
		s++;

	for (size_t i = 0; i < __arraycount(we); i++)
		if (strcmp(we[i], s) == 0)
			return 1;
	return 0;
}