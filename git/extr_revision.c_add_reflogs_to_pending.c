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
struct rev_info {int /*<<< orphan*/  single_worktree; } ;
struct all_refs_cb {unsigned int all_flags; int /*<<< orphan*/ * wt; struct rev_info* all_revs; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_other_reflogs_to_pending (struct all_refs_cb*) ; 
 int /*<<< orphan*/  for_each_reflog (int /*<<< orphan*/ ,struct all_refs_cb*) ; 
 int /*<<< orphan*/  handle_one_reflog ; 

void add_reflogs_to_pending(struct rev_info *revs, unsigned flags)
{
	struct all_refs_cb cb;

	cb.all_revs = revs;
	cb.all_flags = flags;
	cb.wt = NULL;
	for_each_reflog(handle_one_reflog, &cb);

	if (!revs->single_worktree)
		add_other_reflogs_to_pending(&cb);
}