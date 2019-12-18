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
 int /*<<< orphan*/  IBV_SYSFS_PATH_MAX ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 int strlen (char*) ; 
 char* strndup (char const*,int /*<<< orphan*/ ) ; 
 char const* sysfs_path ; 

const char *ibv_get_sysfs_path(void)
{
	const char *env = NULL;

	if (sysfs_path)
		return sysfs_path;

	/*
	 * Only follow use path passed in through the calling user's
	 * environment if we're not running SUID.
	 */
	if (getuid() == geteuid())
		env = getenv("SYSFS_PATH");

	if (env) {
		int len;
		char *dup;

		sysfs_path = dup = strndup(env, IBV_SYSFS_PATH_MAX);
		len = strlen(dup);
		while (len > 0 && dup[len - 1] == '/') {
			--len;
			dup[len] = '\0';
		}
	} else
		sysfs_path = "/sys";

	return sysfs_path;
}