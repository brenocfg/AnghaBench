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
 int RECURSE_SUBMODULES_OFF ; 
 int RECURSE_SUBMODULES_ON ; 
 int config_update_recurse_submodules ; 
 scalar_t__ git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int git_default_submodule_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "submodule.recurse")) {
		int v = git_config_bool(var, value) ?
			RECURSE_SUBMODULES_ON : RECURSE_SUBMODULES_OFF;
		config_update_recurse_submodules = v;
	}
	return 0;
}