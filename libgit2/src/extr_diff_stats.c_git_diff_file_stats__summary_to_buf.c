#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {scalar_t__ mode; int /*<<< orphan*/  path; } ;
struct TYPE_7__ {TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,...) ; 

int git_diff_file_stats__summary_to_buf(
	git_buf *out,
	const git_diff_delta *delta)
{
	if (delta->old_file.mode != delta->new_file.mode) {
		if (delta->old_file.mode == 0) {
			git_buf_printf(out, " create mode %06o %s\n",
				delta->new_file.mode, delta->new_file.path);
		}
		else if (delta->new_file.mode == 0) {
			git_buf_printf(out, " delete mode %06o %s\n",
				delta->old_file.mode, delta->old_file.path);
		}
		else {
			git_buf_printf(out, " mode change %06o => %06o %s\n",
				delta->old_file.mode, delta->new_file.mode, delta->new_file.path);
		}
	}

	return 0;
}