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
struct wt_status_change_data {int dirty_submodule; char worktree_status; scalar_t__ new_submodule_commits; } ;

/* Variables and functions */
 int DIRTY_SUBMODULE_MODIFIED ; 
 int DIRTY_SUBMODULE_UNTRACKED ; 

__attribute__((used)) static char short_submodule_status(struct wt_status_change_data *d)
{
	if (d->new_submodule_commits)
		return 'M';
	if (d->dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
		return 'm';
	if (d->dirty_submodule & DIRTY_SUBMODULE_UNTRACKED)
		return '?';
	return d->worktree_status;
}