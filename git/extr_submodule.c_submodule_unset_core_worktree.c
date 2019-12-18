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
struct submodule {int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_git_common_dir () ; 
 scalar_t__ git_config_set_in_file_gently (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xstrfmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void submodule_unset_core_worktree(const struct submodule *sub)
{
	char *config_path = xstrfmt("%s/modules/%s/config",
				    get_git_common_dir(), sub->name);

	if (git_config_set_in_file_gently(config_path, "core.worktree", NULL))
		warning(_("Could not unset core.worktree setting in submodule '%s'"),
			  sub->path);

	free(config_path);
}