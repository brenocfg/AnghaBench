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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  child_set_env (char***,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  debug3 (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int match_pattern_list (char*,char const*,int /*<<< orphan*/ ) ; 
 char* strstr (char*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
copy_environment_blacklist(char **source, char ***env, u_int *envsize,
    const char *blacklist)
{
	char *var_name, *var_val;
	int i;

	if (source == NULL)
		return;

	for(i = 0; source[i] != NULL; i++) {
		var_name = xstrdup(source[i]);
		if ((var_val = strstr(var_name, "=")) == NULL) {
			free(var_name);
			continue;
		}
		*var_val++ = '\0';

		if (blacklist == NULL ||
		    match_pattern_list(var_name, blacklist, 0) != 1) {
			debug3("Copy environment: %s=%s", var_name, var_val);
			child_set_env(env, envsize, var_name, var_val);
		}

		free(var_name);
	}
}