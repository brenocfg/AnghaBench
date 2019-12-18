#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t git_delta_t ;
struct TYPE_3__ {int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_adds; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_changed_single_one_line_file(
	diff_expects *expected, git_delta_t mod)
{
	cl_assert_equal_i(1, expected->files);
	cl_assert_equal_i(1, expected->file_status[mod]);
	cl_assert_equal_i(1, expected->hunks);
	cl_assert_equal_i(1, expected->lines);

	if (mod == GIT_DELTA_ADDED)
		cl_assert_equal_i(1, expected->line_adds);
	else if (mod == GIT_DELTA_DELETED)
		cl_assert_equal_i(1, expected->line_dels);
}