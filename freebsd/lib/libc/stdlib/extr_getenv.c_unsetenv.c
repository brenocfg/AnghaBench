#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int active; scalar_t__ putenv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int __build_env () ; 
 int /*<<< orphan*/ * __findenv (char const*,size_t,int*,int) ; 
 int __merge_environ () ; 
 int /*<<< orphan*/  __rebuild_environ (int) ; 
 int /*<<< orphan*/  __remove_putenv (int) ; 
 size_t __strleneq (char const*) ; 
 int envActive ; 
 TYPE_1__* envVars ; 
 int envVarsTotal ; 
 int /*<<< orphan*/  errno ; 

int
unsetenv(const char *name)
{
	int envNdx;
	size_t nameLen;
	int newEnvActive;

	/* Check for malformed name. */
	if (name == NULL || (nameLen = __strleneq(name)) == 0) {
		errno = EINVAL;
		return (-1);
	}

	/* Initialize environment. */
	if (__merge_environ() == -1 || (envVars == NULL && __build_env() == -1))
		return (-1);

	/* Deactivate specified variable. */
	/* Remove all occurrences. */
	envNdx = envVarsTotal - 1;
	newEnvActive = envActive;
	while (__findenv(name, nameLen, &envNdx, true) != NULL) {
		envVars[envNdx].active = false;
		if (envVars[envNdx].putenv)
			__remove_putenv(envNdx);
		envNdx--;
		newEnvActive--;
	}
	if (newEnvActive != envActive)
		__rebuild_environ(newEnvActive);

	return (0);
}