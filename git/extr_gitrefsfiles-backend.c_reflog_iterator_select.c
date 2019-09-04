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
struct ref_iterator {int /*<<< orphan*/  refname; } ;
typedef  enum iterator_selection { ____Placeholder_iterator_selection } iterator_selection ;

/* Variables and functions */
 int ITER_DONE ; 
 int ITER_SELECT_0 ; 
 int ITER_SELECT_1 ; 
 int ITER_SKIP_1 ; 
 scalar_t__ REF_TYPE_NORMAL ; 
 scalar_t__ ref_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum iterator_selection reflog_iterator_select(
	struct ref_iterator *iter_worktree,
	struct ref_iterator *iter_common,
	void *cb_data)
{
	if (iter_worktree) {
		/*
		 * We're a bit loose here. We probably should ignore
		 * common refs if they are accidentally added as
		 * per-worktree refs.
		 */
		return ITER_SELECT_0;
	} else if (iter_common) {
		if (ref_type(iter_common->refname) == REF_TYPE_NORMAL)
			return ITER_SELECT_1;

		/*
		 * The main ref store may contain main worktree's
		 * per-worktree refs, which should be ignored
		 */
		return ITER_SKIP_1;
	} else
		return ITER_DONE;
}