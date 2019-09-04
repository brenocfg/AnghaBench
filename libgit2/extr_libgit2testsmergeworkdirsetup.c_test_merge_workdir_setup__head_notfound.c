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
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  annotated_commit_foreach_cb ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int git_repository_mergehead_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_merge_workdir_setup__head_notfound(void)
{
	int error;

	cl_git_fail((error = git_repository_mergehead_foreach(repo,
		annotated_commit_foreach_cb, NULL)));
	cl_assert(error == GIT_ENOTFOUND);
}