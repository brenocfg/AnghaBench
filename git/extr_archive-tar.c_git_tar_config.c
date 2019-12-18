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
 scalar_t__ git_config_int (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int tar_filter_config (char const*,char const*,void*) ; 
 scalar_t__ tar_umask ; 
 scalar_t__ umask (scalar_t__) ; 

__attribute__((used)) static int git_tar_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "tar.umask")) {
		if (value && !strcmp(value, "user")) {
			tar_umask = umask(0);
			umask(tar_umask);
		} else {
			tar_umask = git_config_int(var, value);
		}
		return 0;
	}

	return tar_filter_config(var, value, cb);
}