#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wt_status_change_data {scalar_t__ worktree_status; scalar_t__ dirty_submodule; } ;
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct wt_status {TYPE_2__ change; } ;
struct TYPE_3__ {struct wt_status_change_data* util; } ;

/* Variables and functions */
 scalar_t__ DIFF_STATUS_DELETED ; 
 scalar_t__ DIFF_STATUS_UNMERGED ; 

__attribute__((used)) static int wt_status_check_worktree_changes(struct wt_status *s,
					     int *dirty_submodules)
{
	int i;
	int changes = 0;

	*dirty_submodules = 0;

	for (i = 0; i < s->change.nr; i++) {
		struct wt_status_change_data *d;
		d = s->change.items[i].util;
		if (!d->worktree_status ||
		    d->worktree_status == DIFF_STATUS_UNMERGED)
			continue;
		if (!changes)
			changes = 1;
		if (d->dirty_submodule)
			*dirty_submodules = 1;
		if (d->worktree_status == DIFF_STATUS_DELETED)
			changes = -1;
	}
	return changes;
}