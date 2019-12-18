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
 char** kenvp ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static char *
_getenv_dynamic_locked(const char *name, int *idx)
{
	char *cp;
	int len, i;

	len = strlen(name);
	for (cp = kenvp[0], i = 0; cp != NULL; cp = kenvp[++i]) {
		if ((strncmp(cp, name, len) == 0) &&
		    (cp[len] == '=')) {
			if (idx != NULL)
				*idx = i;
			return (cp + len + 1);
		}
	}
	return (NULL);
}