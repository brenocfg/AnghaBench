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
struct worktree {scalar_t__ is_detached; scalar_t__ is_bare; } ;
struct ref_store {int dummy; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 struct ref_store* get_worktree_ref_store (struct worktree*) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 scalar_t__ is_worktree_being_bisected (struct worktree*,char const*) ; 
 scalar_t__ is_worktree_being_rebased (struct worktree*,char const*) ; 
 char* refs_resolve_ref_unsafe (struct ref_store*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

const struct worktree *find_shared_symref(const char *symref,
					  const char *target)
{
	const struct worktree *existing = NULL;
	static struct worktree **worktrees;
	int i = 0;

	if (worktrees)
		free_worktrees(worktrees);
	worktrees = get_worktrees(0);

	for (i = 0; worktrees[i]; i++) {
		struct worktree *wt = worktrees[i];
		const char *symref_target;
		struct ref_store *refs;
		int flags;

		if (wt->is_bare)
			continue;

		if (wt->is_detached && !strcmp(symref, "HEAD")) {
			if (is_worktree_being_rebased(wt, target)) {
				existing = wt;
				break;
			}
			if (is_worktree_being_bisected(wt, target)) {
				existing = wt;
				break;
			}
		}

		refs = get_worktree_ref_store(wt);
		symref_target = refs_resolve_ref_unsafe(refs, symref, 0,
							NULL, &flags);
		if ((flags & REF_ISSYMREF) &&
		    symref_target && !strcmp(symref_target, target)) {
			existing = wt;
			break;
		}
	}

	return existing;
}