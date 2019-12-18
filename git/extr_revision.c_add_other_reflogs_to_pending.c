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
struct worktree {scalar_t__ is_current; } ;
struct all_refs_cb {struct worktree* wt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 int /*<<< orphan*/  get_worktree_ref_store (struct worktree*) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_one_reflog ; 
 int /*<<< orphan*/  refs_for_each_reflog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct all_refs_cb*) ; 

__attribute__((used)) static void add_other_reflogs_to_pending(struct all_refs_cb *cb)
{
	struct worktree **worktrees, **p;

	worktrees = get_worktrees(0);
	for (p = worktrees; *p; p++) {
		struct worktree *wt = *p;

		if (wt->is_current)
			continue;

		cb->wt = wt;
		refs_for_each_reflog(get_worktree_ref_store(wt),
				     handle_one_reflog,
				     cb);
	}
	free_worktrees(worktrees);
}