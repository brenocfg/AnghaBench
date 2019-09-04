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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_path_exists (char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/ * target ; 
 int /*<<< orphan*/  unmerged_index_init (int /*<<< orphan*/ *,int) ; 

void test_reset_hard__resetting_reverts_unmerged(void)
{
	git_index *index;
	int entries;

	/* Ensure every permutation of non-zero stage entries results in the
	 * path being cleaned up. */
	for (entries = 1; entries < 8; entries++) {
		cl_git_pass(git_repository_index(&index, repo));

		unmerged_index_init(index, entries);
		cl_git_pass(git_index_write(index));

		cl_git_pass(git_revparse_single(&target, repo, "26a125e"));
		cl_git_pass(git_reset(repo, target, GIT_RESET_HARD, NULL));

		cl_assert(git_path_exists("status/conflicting_file") == 0);

		git_object_free(target);
		target = NULL;

		git_index_free(index);
	}
}