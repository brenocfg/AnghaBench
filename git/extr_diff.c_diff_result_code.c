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
struct TYPE_2__ {scalar_t__ check_failed; scalar_t__ has_changes; scalar_t__ exit_with_status; } ;
struct diff_options {int output_format; TYPE_1__ flags; int /*<<< orphan*/  degraded_cc_to_c; int /*<<< orphan*/  needed_rename_limit; } ;

/* Variables and functions */
 int DIFF_FORMAT_CHECKDIFF ; 
 int /*<<< orphan*/  diff_warn_rename_limit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int diff_result_code(struct diff_options *opt, int status)
{
	int result = 0;

	diff_warn_rename_limit("diff.renameLimit",
			       opt->needed_rename_limit,
			       opt->degraded_cc_to_c);
	if (!opt->flags.exit_with_status &&
	    !(opt->output_format & DIFF_FORMAT_CHECKDIFF))
		return status;
	if (opt->flags.exit_with_status &&
	    opt->flags.has_changes)
		result |= 01;
	if ((opt->output_format & DIFF_FORMAT_CHECKDIFF) &&
	    opt->flags.check_failed)
		result |= 02;
	return result;
}