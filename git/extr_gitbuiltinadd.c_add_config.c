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
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  ignore_add_errors ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int add_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "add.ignoreerrors") ||
	    !strcmp(var, "add.ignore-errors")) {
		ignore_add_errors = git_config_bool(var, value);
		return 0;
	}
	return git_default_config(var, value, cb);
}