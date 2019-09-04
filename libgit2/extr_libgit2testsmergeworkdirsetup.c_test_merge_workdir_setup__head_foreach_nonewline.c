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
 int /*<<< orphan*/  GIT_MERGE_HEAD_FILE ; 
 int /*<<< orphan*/  THEIRS_SIMPLE_OID ; 
 int /*<<< orphan*/  annotated_commit_foreach_cb ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int git_repository_mergehead_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  write_file_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_merge_workdir_setup__head_foreach_nonewline(void)
{
	int error;

	write_file_contents(GIT_MERGE_HEAD_FILE, THEIRS_SIMPLE_OID);

	cl_git_fail((error = git_repository_mergehead_foreach(repo,
		annotated_commit_foreach_cb, NULL)));
	cl_assert(error == -1);
}