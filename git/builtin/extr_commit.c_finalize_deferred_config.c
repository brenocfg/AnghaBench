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
struct wt_status {scalar_t__ show_branch; scalar_t__ ahead_behind_flags; scalar_t__ null_termination; } ;
struct TYPE_2__ {scalar_t__ status_format; scalar_t__ show_branch; scalar_t__ ahead_behind; } ;

/* Variables and functions */
 scalar_t__ AHEAD_BEHIND_FULL ; 
 scalar_t__ AHEAD_BEHIND_UNSPECIFIED ; 
 scalar_t__ STATUS_FORMAT_LONG ; 
 scalar_t__ STATUS_FORMAT_NONE ; 
 scalar_t__ STATUS_FORMAT_PORCELAIN ; 
 scalar_t__ STATUS_FORMAT_PORCELAIN_V2 ; 
 scalar_t__ STATUS_FORMAT_UNSPECIFIED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 TYPE_1__ status_deferred_config ; 
 scalar_t__ status_format ; 

__attribute__((used)) static void finalize_deferred_config(struct wt_status *s)
{
	int use_deferred_config = (status_format != STATUS_FORMAT_PORCELAIN &&
				   status_format != STATUS_FORMAT_PORCELAIN_V2 &&
				   !s->null_termination);

	if (s->null_termination) {
		if (status_format == STATUS_FORMAT_NONE ||
		    status_format == STATUS_FORMAT_UNSPECIFIED)
			status_format = STATUS_FORMAT_PORCELAIN;
		else if (status_format == STATUS_FORMAT_LONG)
			die(_("--long and -z are incompatible"));
	}

	if (use_deferred_config && status_format == STATUS_FORMAT_UNSPECIFIED)
		status_format = status_deferred_config.status_format;
	if (status_format == STATUS_FORMAT_UNSPECIFIED)
		status_format = STATUS_FORMAT_NONE;

	if (use_deferred_config && s->show_branch < 0)
		s->show_branch = status_deferred_config.show_branch;
	if (s->show_branch < 0)
		s->show_branch = 0;

	/*
	 * If the user did not give a "--[no]-ahead-behind" command
	 * line argument *AND* we will print in a human-readable format
	 * (short, long etc.) then we inherit from the status.aheadbehind
	 * config setting.  In all other cases (and porcelain V[12] formats
	 * in particular), we inherit _FULL for backwards compatibility.
	 */
	if (use_deferred_config &&
	    s->ahead_behind_flags == AHEAD_BEHIND_UNSPECIFIED)
		s->ahead_behind_flags = status_deferred_config.ahead_behind;

	if (s->ahead_behind_flags == AHEAD_BEHIND_UNSPECIFIED)
		s->ahead_behind_flags = AHEAD_BEHIND_FULL;
}