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
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_RENAME_AND_MODIFY_SOURCE_PATH ; 
 int /*<<< orphan*/  GIT_APPLY_LOCATION_BOTH ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_apply_both__cant_modify_source_path_after_rename(void)
{
	git_diff *diff;

	cl_git_pass(git_diff_from_buffer(&diff, DIFF_RENAME_AND_MODIFY_SOURCE_PATH,
		strlen(DIFF_RENAME_AND_MODIFY_SOURCE_PATH)));
	cl_git_fail(git_apply(repo, diff, GIT_APPLY_LOCATION_BOTH, NULL));

	git_diff_free(diff);
}