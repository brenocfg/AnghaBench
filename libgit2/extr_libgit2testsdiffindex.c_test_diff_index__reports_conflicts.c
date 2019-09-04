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
struct TYPE_3__ {int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_adds; int /*<<< orphan*/  line_ctxt; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_CONFLICTED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_conflicted_diff (TYPE_1__*,int /*<<< orphan*/ ) ; 

void test_diff_index__reports_conflicts(void)
{
	diff_expects exp;

	do_conflicted_diff(&exp, 0);

	cl_assert_equal_i(8, exp.files);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_CONFLICTED]);

	cl_assert_equal_i(7, exp.hunks);

	cl_assert_equal_i(9, exp.lines);
	cl_assert_equal_i(2, exp.line_ctxt);
	cl_assert_equal_i(5, exp.line_adds);
	cl_assert_equal_i(2, exp.line_dels);
}