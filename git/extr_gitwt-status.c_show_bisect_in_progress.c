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
struct TYPE_2__ {scalar_t__ branch; } ;
struct wt_status {scalar_t__ hints; TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wt_longstatus_print_trailer (struct wt_status*) ; 

__attribute__((used)) static void show_bisect_in_progress(struct wt_status *s,
				    const char *color)
{
	if (s->state.branch)
		status_printf_ln(s, color,
				 _("You are currently bisecting, started from branch '%s'."),
				 s->state.branch);
	else
		status_printf_ln(s, color,
				 _("You are currently bisecting."));
	if (s->hints)
		status_printf_ln(s, color,
			_("  (use \"git bisect reset\" to get back to the original branch)"));
	wt_longstatus_print_trailer(s);
}