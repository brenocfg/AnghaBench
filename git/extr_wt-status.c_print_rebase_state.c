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
struct TYPE_2__ {int /*<<< orphan*/  onto; scalar_t__ branch; } ;
struct wt_status {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void print_rebase_state(struct wt_status *s,
			       const char *color)
{
	if (s->state.branch)
		status_printf_ln(s, color,
				 _("You are currently rebasing branch '%s' on '%s'."),
				 s->state.branch,
				 s->state.onto);
	else
		status_printf_ln(s, color,
				 _("You are currently rebasing."));
}