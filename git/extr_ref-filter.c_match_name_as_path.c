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
 unsigned int WM_PATHNAME ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  wildmatch (char const*,char const*,unsigned int) ; 

__attribute__((used)) static int match_name_as_path(const struct ref_filter *filter, const char *refname)
{
	const char **pattern = filter->name_patterns;
	int namelen = strlen(refname);
	unsigned flags = WM_PATHNAME;

	if (filter->ignore_case)
		flags |= WM_CASEFOLD;

	for (; *pattern; pattern++) {
		const char *p = *pattern;
		int plen = strlen(p);

		if ((plen <= namelen) &&
		    !strncmp(refname, p, plen) &&
		    (refname[plen] == '\0' ||
		     refname[plen] == '/' ||
		     p[plen-1] == '/'))
			return 1;
		if (!wildmatch(p, refname, flags))
			return 1;
	}
	return 0;
}