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
 int /*<<< orphan*/  free (char*) ; 
 char* strrchr (char const*,char) ; 
 char const* xstrdup (char const*) ; 

__attribute__((used)) static const char *rstrip_ref_components(const char *refname, int len)
{
	long remaining = len;
	const char *start = xstrdup(refname);
	const char *to_free = start;

	if (len < 0) {
		int i;
		const char *p = refname;

		/* Find total no of '/' separated path-components */
		for (i = 0; p[i]; p[i] == '/' ? i++ : *p++)
			;
		/*
		 * The number of components we need to strip is now
		 * the total minus the components to be left (Plus one
		 * because we count the number of '/', but the number
		 * of components is one more than the no of '/').
		 */
		remaining = i + len + 1;
	}

	while (remaining-- > 0) {
		char *p = strrchr(start, '/');
		if (p == NULL) {
			free((char *)to_free);
			return xstrdup("");
		} else
			p[0] = '\0';
	}
	return start;
}