#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct worktree {scalar_t__ is_current; } ;
struct rev_info {scalar_t__ single_worktree; TYPE_1__* repo; } ;
struct index_state {int /*<<< orphan*/ * member_0; } ;
struct TYPE_2__ {struct index_state* index; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_index (struct index_state*) ; 
 int /*<<< orphan*/  do_add_index_objects_to_pending (struct rev_info*,struct index_state*,unsigned int) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 int /*<<< orphan*/  get_worktree_git_dir (struct worktree*) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 scalar_t__ read_index_from (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_read_index (TYPE_1__*) ; 
 int /*<<< orphan*/  worktree_git_path (struct worktree*,char*) ; 

void add_index_objects_to_pending(struct rev_info *revs, unsigned int flags)
{
	struct worktree **worktrees, **p;

	repo_read_index(revs->repo);
	do_add_index_objects_to_pending(revs, revs->repo->index, flags);

	if (revs->single_worktree)
		return;

	worktrees = get_worktrees(0);
	for (p = worktrees; *p; p++) {
		struct worktree *wt = *p;
		struct index_state istate = { NULL };

		if (wt->is_current)
			continue; /* current index already taken care of */

		if (read_index_from(&istate,
				    worktree_git_path(wt, "index"),
				    get_worktree_git_dir(wt)) > 0)
			do_add_index_objects_to_pending(revs, &istate, flags);
		discard_index(&istate);
	}
	free_worktrees(worktrees);
}