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
 int /*<<< orphan*/  WM_PATHNAME ; 
 scalar_t__ fnmatch_icase_mem (char const*,int,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fspathncmp (char const*,char const*,int) ; 

int match_pathname(const char *pathname, int pathlen,
		   const char *base, int baselen,
		   const char *pattern, int prefix, int patternlen,
		   unsigned flags)
{
	const char *name;
	int namelen;

	/*
	 * match with FNM_PATHNAME; the pattern has base implicitly
	 * in front of it.
	 */
	if (*pattern == '/') {
		pattern++;
		patternlen--;
		prefix--;
	}

	/*
	 * baselen does not count the trailing slash. base[] may or
	 * may not end with a trailing slash though.
	 */
	if (pathlen < baselen + 1 ||
	    (baselen && pathname[baselen] != '/') ||
	    fspathncmp(pathname, base, baselen))
		return 0;

	namelen = baselen ? pathlen - baselen - 1 : pathlen;
	name = pathname + pathlen - namelen;

	if (prefix) {
		/*
		 * if the non-wildcard part is longer than the
		 * remaining pathname, surely it cannot match.
		 */
		if (prefix > namelen)
			return 0;

		if (fspathncmp(pattern, name, prefix))
			return 0;
		pattern += prefix;
		patternlen -= prefix;
		name    += prefix;
		namelen -= prefix;

		/*
		 * If the whole pattern did not have a wildcard,
		 * then our prefix match is all we need; we
		 * do not need to call fnmatch at all.
		 */
		if (!patternlen && !namelen)
			return 1;
	}

	return fnmatch_icase_mem(pattern, patternlen,
				 name, namelen,
				 WM_PATHNAME) == 0;
}