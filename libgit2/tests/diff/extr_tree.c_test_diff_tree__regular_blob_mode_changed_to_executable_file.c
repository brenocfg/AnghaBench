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
struct TYPE_2__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 size_t GIT_DELTA_TYPECHANGE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ expect ; 
 int /*<<< orphan*/  process_tree_to_tree_diffing (char*,char*) ; 

void test_diff_tree__regular_blob_mode_changed_to_executable_file(void)
{
	/*
	 * $ git diff 806999..a8595c
	 * diff --git a/include/Nu/Nu.h b/include/Nu/Nu.h
	 * old mode 100644
	 * new mode 100755
	 */

	process_tree_to_tree_diffing("806999", "a8595c");

	cl_assert_equal_i(1, expect.files);
	cl_assert_equal_i(0, expect.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(1, expect.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(0, expect.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(0, expect.file_status[GIT_DELTA_TYPECHANGE]);
}