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
struct ref_filter {char** name_patterns; scalar_t__ ignore_case; } ;

/* Variables and functions */
 unsigned int WM_CASEFOLD ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  wildmatch (char const*,char const*,unsigned int) ; 

__attribute__((used)) static int match_pattern(const struct ref_filter *filter, const char *refname)
{
	const char **patterns = filter->name_patterns;
	unsigned flags = 0;

	if (filter->ignore_case)
		flags |= WM_CASEFOLD;

	/*
	 * When no '--format' option is given we need to skip the prefix
	 * for matching refs of tags and branches.
	 */
	(void)(skip_prefix(refname, "refs/tags/", &refname) ||
	       skip_prefix(refname, "refs/heads/", &refname) ||
	       skip_prefix(refname, "refs/remotes/", &refname) ||
	       skip_prefix(refname, "refs/", &refname));

	for (; *patterns; patterns++) {
		if (!wildmatch(*patterns, refname, flags))
			return 1;
	}
	return 0;
}