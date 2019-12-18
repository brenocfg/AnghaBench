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
 int __build_env () ; 
 int __merge_environ () ; 
 int __setenv (char const*,size_t,char const*,int) ; 
 size_t __strleneq (char const*) ; 
 int /*<<< orphan*/ * envVars ; 
 int /*<<< orphan*/  errno ; 

int
setenv(const char *name, const char *value, int overwrite)
{
	size_t nameLen;

	/* Check for malformed name. */
	if (name == NULL || (nameLen = __strleneq(name)) == 0) {
		errno = EINVAL;
		return (-1);
	}

	/* Initialize environment. */
	if (__merge_environ() == -1 || (envVars == NULL && __build_env() == -1))
		return (-1);

	return (__setenv(name, nameLen, value, overwrite));
}