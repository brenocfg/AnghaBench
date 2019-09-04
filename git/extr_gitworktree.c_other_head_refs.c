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
struct object_id {int dummy; } ;
typedef  int (* each_ref_fn ) (int /*<<< orphan*/ ,struct object_id*,int,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refs_read_ref_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  worktree_ref (struct worktree*,char*) ; 

int other_head_refs(each_ref_fn fn, void *cb_data)
{
	struct worktree **worktrees, **p;
	int ret = 0;

	worktrees = get_worktrees(0);
	for (p = worktrees; *p; p++) {
		struct worktree *wt = *p;
		struct object_id oid;
		int flag;

		if (wt->is_current)
			continue;

		if (!refs_read_ref_full(get_main_ref_store(the_repository),
					worktree_ref(wt, "HEAD"),
					RESOLVE_REF_READING,
					&oid, &flag))
			ret = fn(worktree_ref(wt, "HEAD"), &oid, flag, cb_data);
		if (ret)
			break;
	}
	free_worktrees(worktrees);
	return ret;
}