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
struct worktree {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 char const* get_git_common_dir () ; 
 char const* get_git_dir () ; 
 char const* git_common_path (char*,int /*<<< orphan*/ ) ; 

const char *get_worktree_git_dir(const struct worktree *wt)
{
	if (!wt)
		return get_git_dir();
	else if (!wt->id)
		return get_git_common_dir();
	else
		return git_common_path("worktrees/%s", wt->id);
}