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
struct TYPE_2__ {scalar_t__ merge_in_progress; } ;
struct wt_status {int committable; TYPE_1__ state; scalar_t__ branch; int /*<<< orphan*/  repo; scalar_t__ is_initial; } ;

/* Variables and functions */
 int /*<<< orphan*/  has_unmerged (struct wt_status*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  trace2_region_enter (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_region_leave (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wt_status_collect_changes_index (struct wt_status*) ; 
 int /*<<< orphan*/  wt_status_collect_changes_initial (struct wt_status*) ; 
 int /*<<< orphan*/  wt_status_collect_changes_worktree (struct wt_status*) ; 
 int /*<<< orphan*/  wt_status_collect_untracked (struct wt_status*) ; 
 int /*<<< orphan*/  wt_status_get_state (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void wt_status_collect(struct wt_status *s)
{
	trace2_region_enter("status", "worktrees", s->repo);
	wt_status_collect_changes_worktree(s);
	trace2_region_leave("status", "worktrees", s->repo);

	if (s->is_initial) {
		trace2_region_enter("status", "initial", s->repo);
		wt_status_collect_changes_initial(s);
		trace2_region_leave("status", "initial", s->repo);
	} else {
		trace2_region_enter("status", "index", s->repo);
		wt_status_collect_changes_index(s);
		trace2_region_leave("status", "index", s->repo);
	}

	trace2_region_enter("status", "untracked", s->repo);
	wt_status_collect_untracked(s);
	trace2_region_leave("status", "untracked", s->repo);

	wt_status_get_state(s->repo, &s->state, s->branch && !strcmp(s->branch, "HEAD"));
	if (s->state.merge_in_progress && !has_unmerged(s))
		s->committable = 1;
}