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
struct wt_status {scalar_t__ hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ has_unmerged (struct wt_status*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wt_longstatus_print_trailer (struct wt_status*) ; 

__attribute__((used)) static void show_merge_in_progress(struct wt_status *s,
				   const char *color)
{
	if (has_unmerged(s)) {
		status_printf_ln(s, color, _("You have unmerged paths."));
		if (s->hints) {
			status_printf_ln(s, color,
					 _("  (fix conflicts and run \"git commit\")"));
			status_printf_ln(s, color,
					 _("  (use \"git merge --abort\" to abort the merge)"));
		}
	} else {
		status_printf_ln(s, color,
			_("All conflicts fixed but you are still merging."));
		if (s->hints)
			status_printf_ln(s, color,
				_("  (use \"git commit\" to conclude merge)"));
	}
	wt_longstatus_print_trailer(s);
}