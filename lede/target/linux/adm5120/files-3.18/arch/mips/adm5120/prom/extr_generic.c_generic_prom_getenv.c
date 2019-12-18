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
 char** _prom_envp ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

char *generic_prom_getenv(char *envname)
{
	char **env;
	char *ret;

	ret = NULL;
	for (env = _prom_envp; *env != NULL; env++) {
		if (strcmp(envname, *env++) == 0) {
			ret = *env;
			break;
		}
	}

	return ret;
}