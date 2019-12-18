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
struct TYPE_2__ {int /*<<< orphan*/  revert_head_oid; } ;
struct wt_status {TYPE_1__ state; scalar_t__ hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  find_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ has_unmerged (struct wt_status*) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wt_longstatus_print_trailer (struct wt_status*) ; 

__attribute__((used)) static void show_revert_in_progress(struct wt_status *s,
				    const char *color)
{
	if (is_null_oid(&s->state.revert_head_oid))
		status_printf_ln(s, color,
			_("Revert currently in progress."));
	else
		status_printf_ln(s, color,
			_("You are currently reverting commit %s."),
			find_unique_abbrev(&s->state.revert_head_oid,
					   DEFAULT_ABBREV));
	if (s->hints) {
		if (has_unmerged(s))
			status_printf_ln(s, color,
				_("  (fix conflicts and run \"git revert --continue\")"));
		else if (is_null_oid(&s->state.revert_head_oid))
			status_printf_ln(s, color,
				_("  (run \"git revert --continue\" to continue)"));
		else
			status_printf_ln(s, color,
				_("  (all conflicts fixed: run \"git revert --continue\")"));
		status_printf_ln(s, color,
			_("  (use \"git revert --skip\" to skip this patch)"));
		status_printf_ln(s, color,
			_("  (use \"git revert --abort\" to cancel the revert operation)"));
	}
	wt_longstatus_print_trailer(s);
}