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
struct wt_status {scalar_t__ whence; int /*<<< orphan*/  reference; int /*<<< orphan*/  is_initial; int /*<<< orphan*/  hints; } ;

/* Variables and functions */
 scalar_t__ FROM_COMMIT ; 
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wt_longstatus_print_cached_header(struct wt_status *s)
{
	const char *c = color(WT_STATUS_HEADER, s);

	status_printf_ln(s, c, _("Changes to be committed:"));
	if (!s->hints)
		return;
	if (s->whence != FROM_COMMIT)
		; /* NEEDSWORK: use "git reset --unresolve"??? */
	else if (!s->is_initial) {
		if (!strcmp(s->reference, "HEAD"))
			status_printf_ln(s, c
					 , _("  (use \"git restore --staged <file>...\" to unstage)"));
		else
			status_printf_ln(s, c,
					 _("  (use \"git restore --source=%s --staged <file>...\" to unstage)"),
					 s->reference);
	} else
		status_printf_ln(s, c, _("  (use \"git rm --cached <file>...\" to unstage)"));
}