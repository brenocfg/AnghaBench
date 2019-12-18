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
 int /*<<< orphan*/  EINVAL ; 
 char* __findenv (char const*,size_t,int*,int) ; 
 char* __findenv_environ (char const*,size_t) ; 
 size_t __strleneq (char const*) ; 
 int /*<<< orphan*/ * envVars ; 
 int envVarsTotal ; 
 int /*<<< orphan*/ ** environ ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ ** intEnviron ; 

char *
getenv(const char *name)
{
	int envNdx;
	size_t nameLen;

	/* Check for malformed name. */
	if (name == NULL || (nameLen = __strleneq(name)) == 0) {
		errno = EINVAL;
		return (NULL);
	}

	/*
	 * Variable search order:
	 * 1. Check for an empty environ.  This allows an application to clear
	 *    the environment.
	 * 2. Search the external environ array.
	 * 3. Search the internal environment.
	 *
	 * Since malloc() depends upon getenv(), getenv() must never cause the
	 * internal environment storage to be generated.
	 */
	if (environ == NULL || environ[0] == NULL)
		return (NULL);
	else if (envVars == NULL || environ != intEnviron)
		return (__findenv_environ(name, nameLen));
	else {
		envNdx = envVarsTotal - 1;
		return (__findenv(name, nameLen, &envNdx, true));
	}
}