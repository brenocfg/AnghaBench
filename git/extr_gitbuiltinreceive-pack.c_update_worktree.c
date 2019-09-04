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
struct argv_array {int dummy; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  absolute_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 char* git_work_tree_cfg ; 
 scalar_t__ is_bare_repository () ; 
 char* push_to_checkout (unsigned char*,struct argv_array*,char const*) ; 
 int /*<<< orphan*/  push_to_checkout_hook ; 
 char* push_to_deploy (unsigned char*,struct argv_array*,char const*) ; 

__attribute__((used)) static const char *update_worktree(unsigned char *sha1)
{
	const char *retval;
	const char *work_tree = git_work_tree_cfg ? git_work_tree_cfg : "..";
	struct argv_array env = ARGV_ARRAY_INIT;

	if (is_bare_repository())
		return "denyCurrentBranch = updateInstead needs a worktree";

	argv_array_pushf(&env, "GIT_DIR=%s", absolute_path(get_git_dir()));

	if (!find_hook(push_to_checkout_hook))
		retval = push_to_deploy(sha1, &env, work_tree);
	else
		retval = push_to_checkout(sha1, &env, work_tree);

	argv_array_clear(&env);
	return retval;
}