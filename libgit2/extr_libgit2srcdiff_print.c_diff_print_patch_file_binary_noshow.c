#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  path; } ;
struct TYPE_13__ {int /*<<< orphan*/  path; } ;
struct TYPE_16__ {TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_4__ git_diff_delta ;
struct TYPE_17__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_5__ git_buf ;
struct TYPE_15__ {int num_lines; } ;
struct TYPE_18__ {int /*<<< orphan*/  buf; TYPE_3__ line; } ;
typedef  TYPE_6__ diff_print_info ;

/* Variables and functions */
 TYPE_5__ GIT_BUF_INIT ; 
 int diff_delta_format_path (TYPE_5__*,char const*,int /*<<< orphan*/ ) ; 
 int diff_delta_format_with_paths (int /*<<< orphan*/ ,TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_5__*) ; 

__attribute__((used)) static int diff_print_patch_file_binary_noshow(
	diff_print_info *pi, git_diff_delta *delta,
	const char *old_pfx, const char *new_pfx)
{
	git_buf old_path = GIT_BUF_INIT, new_path = GIT_BUF_INIT;
	int error;

	if ((error = diff_delta_format_path(
			&old_path, old_pfx, delta->old_file.path)) < 0 ||
		(error = diff_delta_format_path(
			&new_path, new_pfx, delta->new_file.path)) < 0)
		goto done;

	pi->line.num_lines = 1;
	error = diff_delta_format_with_paths(
		pi->buf, delta, "Binary files %s and %s differ\n",
		old_path.ptr, new_path.ptr);

done:
	git_buf_dispose(&old_path);
	git_buf_dispose(&new_path);

	return error;
}