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
 int /*<<< orphan*/  EXEC_PATH_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_EXEC_PATH ; 
 char const* exec_path_value ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 char* system_path (int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

const char *git_exec_path(void)
{
	if (!exec_path_value) {
		const char *env = getenv(EXEC_PATH_ENVIRONMENT);
		if (env && *env)
			exec_path_value = xstrdup(env);
		else
			exec_path_value = system_path(GIT_EXEC_PATH);
	}
	return exec_path_value;
}