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
struct TYPE_2__ {scalar_t__ am_empty_patch; } ;
struct wt_status {TYPE_1__ state; scalar_t__ hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wt_longstatus_print_trailer (struct wt_status*) ; 

__attribute__((used)) static void show_am_in_progress(struct wt_status *s,
				const char *color)
{
	status_printf_ln(s, color,
		_("You are in the middle of an am session."));
	if (s->state.am_empty_patch)
		status_printf_ln(s, color,
			_("The current patch is empty."));
	if (s->hints) {
		if (!s->state.am_empty_patch)
			status_printf_ln(s, color,
				_("  (fix conflicts and then run \"git am --continue\")"));
		status_printf_ln(s, color,
			_("  (use \"git am --skip\" to skip this patch)"));
		status_printf_ln(s, color,
			_("  (use \"git am --abort\" to restore the original branch)"));
	}
	wt_longstatus_print_trailer(s);
}