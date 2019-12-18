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
 int /*<<< orphan*/  CorruptEnvValueMsg ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  __clean_env (int) ; 
 int /*<<< orphan*/  __env_warnx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int __setenv (char*,int,char*,int) ; 
 scalar_t__ envActive ; 
 char** environ ; 
 int /*<<< orphan*/  errno ; 
 char** intEnviron ; 
 char** origEnviron ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
__merge_environ(void)
{
	char **env;
	char *equals;

	/*
	 * Internally-built environ has been replaced or cleared (detected by
	 * using the count of active variables against a NULL as the first value
	 * in environ).  Clean up everything.
	 */
	if (intEnviron != NULL && (environ != intEnviron || (envActive > 0 &&
	    environ[0] == NULL))) {
		/* Deactivate all environment variables. */
		if (envActive > 0) {
			origEnviron = NULL;
			__clean_env(false);
		}

		/*
		 * Insert new environ into existing, yet deactivated,
		 * environment array.
		 */
		origEnviron = environ;
		if (origEnviron != NULL)
			for (env = origEnviron; *env != NULL; env++) {
				if ((equals = strchr(*env, '=')) == NULL) {
					__env_warnx(CorruptEnvValueMsg, *env,
					    strlen(*env));
					errno = EFAULT;
					return (-1);
				}
				if (__setenv(*env, equals - *env, equals + 1,
				    1) == -1)
					return (-1);
			}
	}

	return (0);
}