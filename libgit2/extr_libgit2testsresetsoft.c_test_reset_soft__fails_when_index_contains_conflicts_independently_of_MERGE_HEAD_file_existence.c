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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EUNMERGED ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_SOFT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_has_conflicts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  target ; 

void test_reset_soft__fails_when_index_contains_conflicts_independently_of_MERGE_HEAD_file_existence(void)
{
	git_index *index;
	git_reference *head;
	git_buf merge_head_path = GIT_BUF_INIT;

	cl_git_sandbox_cleanup();

	repo = cl_git_sandbox_init("mergedrepo");

	cl_git_pass(git_buf_joinpath(&merge_head_path, git_repository_path(repo), "MERGE_HEAD"));
	cl_git_pass(p_unlink(git_buf_cstr(&merge_head_path)));
	git_buf_dispose(&merge_head_path);

	cl_git_pass(git_repository_index(&index, repo));
	cl_assert_equal_i(true, git_index_has_conflicts(index));
	git_index_free(index);

	cl_git_pass(git_repository_head(&head, repo));
	cl_git_pass(git_reference_peel(&target, head, GIT_OBJECT_COMMIT));
	git_reference_free(head);

	cl_assert_equal_i(GIT_EUNMERGED, git_reset(repo, target, GIT_RESET_SOFT, NULL));
}