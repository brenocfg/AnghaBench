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
struct wt_status_state {int bisect_in_progress; int /*<<< orphan*/  branch; } ;
struct worktree {int dummy; } ;
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_branch (struct worktree const*,char*) ; 
 int /*<<< orphan*/  stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  worktree_git_path (struct worktree const*,char*) ; 

int wt_status_check_bisect(const struct worktree *wt,
			   struct wt_status_state *state)
{
	struct stat st;

	if (!stat(worktree_git_path(wt, "BISECT_LOG"), &st)) {
		state->bisect_in_progress = 1;
		state->branch = get_branch(wt, "BISECT_START");
		return 1;
	}
	return 0;
}