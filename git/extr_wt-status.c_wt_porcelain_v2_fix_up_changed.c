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
struct wt_status_change_data {scalar_t__ mode_head; scalar_t__ mode_index; scalar_t__ mode_worktree; int /*<<< orphan*/  worktree_status; int /*<<< orphan*/  oid_index; int /*<<< orphan*/  oid_head; int /*<<< orphan*/  index_status; } ;
struct string_list_item {struct wt_status_change_data* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wt_porcelain_v2_fix_up_changed(struct string_list_item *it)
{
	struct wt_status_change_data *d = it->util;

	if (!d->index_status) {
		/*
		 * This entry is unchanged in the index (relative to the head).
		 * Therefore, the collect_updated_cb was never called for this
		 * entry (during the head-vs-index scan) and so the head column
		 * fields were never set.
		 *
		 * We must have data for the index column (from the
		 * index-vs-worktree scan (otherwise, this entry should not be
		 * in the list of changes)).
		 *
		 * Copy index column fields to the head column, so that our
		 * output looks complete.
		 */
		assert(d->mode_head == 0);
		d->mode_head = d->mode_index;
		oidcpy(&d->oid_head, &d->oid_index);
	}

	if (!d->worktree_status) {
		/*
		 * This entry is unchanged in the worktree (relative to the index).
		 * Therefore, the collect_changed_cb was never called for this entry
		 * (during the index-vs-worktree scan) and so the worktree column
		 * fields were never set.
		 *
		 * We must have data for the index column (from the head-vs-index
		 * scan).
		 *
		 * Copy the index column fields to the worktree column so that
		 * our output looks complete.
		 *
		 * Note that we only have a mode field in the worktree column
		 * because the scan code tries really hard to not have to compute it.
		 */
		assert(d->mode_worktree == 0);
		d->mode_worktree = d->mode_index;
	}
}