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
struct worktree {int is_detached; int /*<<< orphan*/  head_ref; int /*<<< orphan*/  head_oid; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  get_worktree_ref_store (struct worktree*) ; 
 char* refs_resolve_ref_unsafe (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void add_head_info(struct worktree *wt)
{
	int flags;
	const char *target;

	target = refs_resolve_ref_unsafe(get_worktree_ref_store(wt),
					 "HEAD",
					 0,
					 &wt->head_oid, &flags);
	if (!target)
		return;

	if (flags & REF_ISSYMREF)
		wt->head_ref = xstrdup(target);
	else
		wt->is_detached = 1;
}