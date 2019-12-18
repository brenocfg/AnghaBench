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
 int /*<<< orphan*/  _ (char*) ; 
 char* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wt_longstatus_print_dirty_header(struct wt_status *s,
					     int has_deleted,
					     int has_dirty_submodules)
{
	const char *c = color(WT_STATUS_HEADER, s);

	status_printf_ln(s, c, _("Changes not staged for commit:"));
	if (!s->hints)
		return;
	if (!has_deleted)
		status_printf_ln(s, c, _("  (use \"git add <file>...\" to update what will be committed)"));
	else
		status_printf_ln(s, c, _("  (use \"git add/rm <file>...\" to update what will be committed)"));
	status_printf_ln(s, c, _("  (use \"git restore <file>...\" to discard changes in working directory)"));
	if (has_dirty_submodules)
		status_printf_ln(s, c, _("  (commit or discard the untracked or modified content in submodules)"));
}