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
struct TYPE_2__ {int active; size_t valueSize; size_t nameLen; char* value; int /*<<< orphan*/ * name; scalar_t__ putenv; } ;

/* Variables and functions */
 int /*<<< orphan*/  __enlarge_env () ; 
 int /*<<< orphan*/ * __findenv (char const*,size_t,int*,int) ; 
 int __rebuild_environ (int) ; 
 int /*<<< orphan*/  __remove_putenv (int) ; 
 int envActive ; 
 TYPE_1__* envVars ; 
 int envVarsTotal ; 
 int /*<<< orphan*/ * malloc (int) ; 
 char* stpncpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
__setenv(const char *name, size_t nameLen, const char *value, int overwrite)
{
	bool reuse;
	char *env;
	int envNdx;
	int newEnvActive;
	size_t valueLen;

	/* Find existing environment variable large enough to use. */
	envNdx = envVarsTotal - 1;
	newEnvActive = envActive;
	valueLen = strlen(value);
	reuse = false;
	if (__findenv(name, nameLen, &envNdx, false) != NULL) {
		/* Deactivate entry if overwrite is allowed. */
		if (envVars[envNdx].active) {
			if (overwrite == 0)
				return (0);
			envVars[envNdx].active = false;
			newEnvActive--;
		}

		/* putenv() created variable cannot be reused. */
		if (envVars[envNdx].putenv)
			__remove_putenv(envNdx);

		/* Entry is large enough to reuse. */
		else if (envVars[envNdx].valueSize >= valueLen)
			reuse = true;
	}

	/* Create new variable if none was found of sufficient size. */
	if (! reuse) {
		/* Enlarge environment. */
		envNdx = envVarsTotal;
		if (!__enlarge_env())
			return (-1);

		/* Create environment entry. */
		envVars[envNdx].name = malloc(nameLen + sizeof ("=") +
		    valueLen);
		if (envVars[envNdx].name == NULL) {
			envVarsTotal--;
			return (-1);
		}
		envVars[envNdx].nameLen = nameLen;
		envVars[envNdx].valueSize = valueLen;

		/* Save name of name/value pair. */
		env = stpncpy(envVars[envNdx].name, name, nameLen);
		*env++ = '=';
	}
	else
		env = envVars[envNdx].value;

	/* Save value of name/value pair. */
	strcpy(env, value);
	envVars[envNdx].value = env;
	envVars[envNdx].active = true;
	newEnvActive++;

	/* No need to rebuild environ if an active variable was reused. */
	if (reuse && newEnvActive == envActive)
		return (0);
	else
		return (__rebuild_environ(newEnvActive));
}