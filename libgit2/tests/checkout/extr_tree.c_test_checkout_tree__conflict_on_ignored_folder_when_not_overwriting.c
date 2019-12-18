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

/* Variables and functions */
 int GIT_CHECKOUT_DONT_OVERWRITE_IGNORED ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_ECONFLICT ; 
 int checkout_tree_with_blob_ignored_in_workdir (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 

void test_checkout_tree__conflict_on_ignored_folder_when_not_overwriting(void)
{
	int error;

	cl_git_fail(error = checkout_tree_with_blob_ignored_in_workdir(
		GIT_CHECKOUT_SAFE | GIT_CHECKOUT_DONT_OVERWRITE_IGNORED, true));

	cl_assert_equal_i(GIT_ECONFLICT, error);
}