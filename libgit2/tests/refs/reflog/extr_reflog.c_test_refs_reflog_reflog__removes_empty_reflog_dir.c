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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 char* GIT_REFLOG_DIR ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_master_tip ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_isfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_refs_reflog_reflog__removes_empty_reflog_dir(void)
{
	git_reference *ref;
	git_buf log_path = GIT_BUF_INIT;
	git_oid id;

	/* Create a new branch pointing at the HEAD */
	git_oid_fromstr(&id, current_master_tip);
	cl_git_pass(git_reference_create(&ref, g_repo, "refs/heads/new-dir/new-head", &id, 0, NULL));

	git_buf_joinpath(&log_path, git_repository_path(g_repo), GIT_REFLOG_DIR);
	git_buf_joinpath(&log_path, git_buf_cstr(&log_path), "refs/heads/new-dir/new-head");

	cl_assert_equal_i(true, git_path_isfile(git_buf_cstr(&log_path)));

	cl_git_pass(git_reference_delete(ref));
	git_reference_free(ref);

	/* new ref creation should succeed since new-dir is empty */
	git_oid_fromstr(&id, current_master_tip);
	cl_git_pass(git_reference_create(&ref, g_repo, "refs/heads/new-dir", &id, 0, NULL));
	git_reference_free(ref);

	git_buf_dispose(&log_path);
}