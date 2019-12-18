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
struct mod_depend {int dummy; } ;

/* Variables and functions */
 char* linker_hints_lookup (char*,int,char const*,int,struct mod_depend const*) ; 
 char* linker_path ; 

__attribute__((used)) static char *
linker_search_module(const char *modname, int modnamelen,
    const struct mod_depend *verinfo)
{
	char *cp, *ep, *result;

	/*
	 * traverse the linker path
	 */
	for (cp = linker_path; *cp; cp = ep + 1) {
		/* find the end of this component */
		for (ep = cp; (*ep != 0) && (*ep != ';'); ep++);
		result = linker_hints_lookup(cp, ep - cp, modname,
		    modnamelen, verinfo);
		if (result != NULL)
			return (result);
		if (*ep == 0)
			break;
	}
	return (NULL);
}