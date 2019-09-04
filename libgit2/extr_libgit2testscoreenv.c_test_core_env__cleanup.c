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
 int NUM_VARS ; 
 int /*<<< orphan*/  cl_sandbox_set_search_path_defaults () ; 
 int /*<<< orphan*/  cl_setenv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** env_save ; 
 int /*<<< orphan*/ * env_vars ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 char** home_values ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 

void test_core_env__cleanup(void)
{
	int i;
	char **val;

	for (i = 0; i < NUM_VARS; ++i) {
		cl_setenv(env_vars[i], env_save[i]);
		git__free(env_save[i]);
		env_save[i] = NULL;
	}

	/* these will probably have already been cleaned up, but if a test
	 * fails, then it's probably good to try and clear out these dirs
	 */
	for (val = home_values; *val != NULL; val++) {
		if (**val != '\0')
			(void)p_rmdir(*val);
	}

	cl_sandbox_set_search_path_defaults();
}