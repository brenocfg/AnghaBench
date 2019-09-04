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
struct wt_status {scalar_t__ whence; char* reference; int /*<<< orphan*/  is_initial; int /*<<< orphan*/  hints; } ;

/* Variables and functions */
 scalar_t__ FROM_COMMIT ; 
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 char* _ (char*) ; 
 char* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,char*,...) ; 

__attribute__((used)) static void wt_longstatus_print_cached_header(struct wt_status *s)
{
	const char *c = color(WT_STATUS_HEADER, s);

	status_printf_ln(s, c, _("Changes to be committed:"));
	if (!s->hints)
		return;
	if (s->whence != FROM_COMMIT)
		; /* NEEDSWORK: use "git reset --unresolve"??? */
	else if (!s->is_initial)
		status_printf_ln(s, c, _("  (use \"git reset %s <file>...\" to unstage)"), s->reference);
	else
		status_printf_ln(s, c, _("  (use \"git rm --cached <file>...\" to unstage)"));
	status_printf_ln(s, c, "%s", "");
}