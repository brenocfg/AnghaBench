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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  connect_work_tree_and_git_dir (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ rename (char const*,char const*) ; 

void relocate_gitdir(const char *path, const char *old_git_dir, const char *new_git_dir)
{
	if (rename(old_git_dir, new_git_dir) < 0)
		die_errno(_("could not migrate git directory from '%s' to '%s'"),
			old_git_dir, new_git_dir);

	connect_work_tree_and_git_dir(path, new_git_dir, 0);
}