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
struct wt_status {int /*<<< orphan*/  hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 char* _ (char*) ; 
 char* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,char*,char const*) ; 

__attribute__((used)) static void wt_longstatus_print_other_header(struct wt_status *s,
					     const char *what,
					     const char *how)
{
	const char *c = color(WT_STATUS_HEADER, s);
	status_printf_ln(s, c, "%s:", what);
	if (!s->hints)
		return;
	status_printf_ln(s, c, _("  (use \"git %s <file>...\" to include in what will be committed)"), how);
}