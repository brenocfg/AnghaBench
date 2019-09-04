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
 int /*<<< orphan*/  GIT_WORK_TREE_ENVIRONMENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ chdir_notify (char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 char* get_git_work_tree () ; 
 scalar_t__ getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ work_tree_config_is_bogus ; 

void setup_work_tree(void)
{
	const char *work_tree;
	static int initialized = 0;

	if (initialized)
		return;

	if (work_tree_config_is_bogus)
		die(_("unable to set up work tree using invalid config"));

	work_tree = get_git_work_tree();
	if (!work_tree || chdir_notify(work_tree))
		die(_("this operation must be run in a work tree"));

	/*
	 * Make sure subsequent git processes find correct worktree
	 * if $GIT_WORK_TREE is set relative
	 */
	if (getenv(GIT_WORK_TREE_ENVIRONMENT))
		setenv(GIT_WORK_TREE_ENVIRONMENT, ".", 1);

	initialized = 1;
}