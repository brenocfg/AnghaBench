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
 int /*<<< orphan*/  M_LINKER ; 
 char* linker_lookup_file (char*,int,char const*,int,int /*<<< orphan*/ *) ; 
 char* linker_path ; 
 scalar_t__ strchr (char const*,char) ; 
 char* strdup (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
linker_search_kld(const char *name)
{
	char *cp, *ep, *result;
	int len;

	/* qualified at all? */
	if (strchr(name, '/'))
		return (strdup(name, M_LINKER));

	/* traverse the linker path */
	len = strlen(name);
	for (ep = linker_path; *ep; ep++) {
		cp = ep;
		/* find the end of this component */
		for (; *ep != 0 && *ep != ';'; ep++);
		result = linker_lookup_file(cp, ep - cp, name, len, NULL);
		if (result != NULL)
			return (result);
	}
	return (NULL);
}