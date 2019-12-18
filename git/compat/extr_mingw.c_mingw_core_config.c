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
 int /*<<< orphan*/  HIDE_DOTFILES_DOTGITONLY ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int /*<<< orphan*/  hide_dotfiles ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  unset_environment_variables ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

int mingw_core_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "core.hidedotfiles")) {
		if (value && !strcasecmp(value, "dotgitonly"))
			hide_dotfiles = HIDE_DOTFILES_DOTGITONLY;
		else
			hide_dotfiles = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.unsetenvvars")) {
		free(unset_environment_variables);
		unset_environment_variables = xstrdup(value);
		return 0;
	}

	return 0;
}