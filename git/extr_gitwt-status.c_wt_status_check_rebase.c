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
struct wt_status_state {int am_in_progress; int am_empty_patch; int rebase_in_progress; int rebase_interactive_in_progress; void* onto; void* branch; } ;
struct worktree {int dummy; } ;
struct stat {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 void* get_branch (struct worktree const*,char*) ; 
 int /*<<< orphan*/  stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  worktree_git_path (struct worktree const*,char*) ; 

int wt_status_check_rebase(const struct worktree *wt,
			   struct wt_status_state *state)
{
	struct stat st;

	if (!stat(worktree_git_path(wt, "rebase-apply"), &st)) {
		if (!stat(worktree_git_path(wt, "rebase-apply/applying"), &st)) {
			state->am_in_progress = 1;
			if (!stat(worktree_git_path(wt, "rebase-apply/patch"), &st) && !st.st_size)
				state->am_empty_patch = 1;
		} else {
			state->rebase_in_progress = 1;
			state->branch = get_branch(wt, "rebase-apply/head-name");
			state->onto = get_branch(wt, "rebase-apply/onto");
		}
	} else if (!stat(worktree_git_path(wt, "rebase-merge"), &st)) {
		if (!stat(worktree_git_path(wt, "rebase-merge/interactive"), &st))
			state->rebase_interactive_in_progress = 1;
		else
			state->rebase_in_progress = 1;
		state->branch = get_branch(wt, "rebase-merge/head-name");
		state->onto = get_branch(wt, "rebase-merge/onto");
	} else
		return 0;
	return 1;
}