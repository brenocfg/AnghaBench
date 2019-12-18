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
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

int
wild_jail_match(const char *jname, const char *wname)
{
	const char *jc, *jd, *wc, *wd;

	/*
	 * A non-final "*" component in the wild name matches a single jail
	 * component, and a final "*" matches one or more jail components.
	 */
	for (jc = jname, wc = wname;
	     (jd = strchr(jc, '.')) && (wd = strchr(wc, '.'));
	     jc = jd + 1, wc = wd + 1)
		if (strncmp(jc, wc, jd - jc + 1) && strncmp(wc, "*.", 2))
			return 0;
	return (!strcmp(jc, wc) || !strcmp(wc, "*"));
}