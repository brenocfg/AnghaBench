#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_EEXISTS ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  add_submodule_with_commit (char*) ; 
 int /*<<< orphan*/  assert_submodule_exists (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  baseline_tests () ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_add_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_add_setup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refute_submodule_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void test_submodule_lookup__just_added(void)
{
	git_submodule *sm;
	git_buf snap1 = GIT_BUF_INIT, snap2 = GIT_BUF_INIT;
	git_reference *original_head = NULL;

	refute_submodule_exists(g_repo, "sm_just_added", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "sm_just_added_2", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "sm_just_added_idx", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "sm_just_added_head", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "mismatch_name", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "mismatch_path", GIT_ENOTFOUND);
	baseline_tests();

	cl_git_pass(git_futils_readbuffer(&snap1, "submod2/.gitmodules"));
	cl_git_pass(git_repository_head(&original_head, g_repo));

	cl_git_pass(git_submodule_add_setup(&sm, g_repo,
		"https://github.com/libgit2/libgit2.git", "sm_just_added", 1));
	git_submodule_free(sm);
	assert_submodule_exists(g_repo, "sm_just_added");

	cl_git_pass(git_submodule_add_setup(&sm, g_repo,
		"https://github.com/libgit2/libgit2.git", "sm_just_added_2", 1));
	assert_submodule_exists(g_repo, "sm_just_added_2");
	cl_git_fail(git_submodule_add_finalize(sm)); /* fails if no HEAD */
	git_submodule_free(sm);

	add_submodule_with_commit("sm_just_added_head");
	cl_repo_commit_from_index(NULL, g_repo, NULL, 0, "commit new sm to head");
	assert_submodule_exists(g_repo, "sm_just_added_head");

	add_submodule_with_commit("sm_just_added_idx");
	assert_submodule_exists(g_repo, "sm_just_added_idx");

	cl_git_pass(git_futils_readbuffer(&snap2, "submod2/.gitmodules"));

	cl_git_append2file(
		"submod2/.gitmodules",
		"\n[submodule \"mismatch_name\"]\n"
		"\tpath = mismatch_path\n"
		"\turl = https://example.com/example.git\n\n");

	assert_submodule_exists(g_repo, "mismatch_name");
	assert_submodule_exists(g_repo, "mismatch_path");
	assert_submodule_exists(g_repo, "sm_just_added");
	assert_submodule_exists(g_repo, "sm_just_added_2");
	assert_submodule_exists(g_repo, "sm_just_added_idx");
	assert_submodule_exists(g_repo, "sm_just_added_head");
	baseline_tests();

	cl_git_rewritefile("submod2/.gitmodules", snap2.ptr);
	git_buf_dispose(&snap2);

	refute_submodule_exists(g_repo, "mismatch_name", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "mismatch_path", GIT_ENOTFOUND);
	assert_submodule_exists(g_repo, "sm_just_added");
	assert_submodule_exists(g_repo, "sm_just_added_2");
	assert_submodule_exists(g_repo, "sm_just_added_idx");
	assert_submodule_exists(g_repo, "sm_just_added_head");
	baseline_tests();

	cl_git_rewritefile("submod2/.gitmodules", snap1.ptr);
	git_buf_dispose(&snap1);

	refute_submodule_exists(g_repo, "mismatch_name", GIT_ENOTFOUND);
	refute_submodule_exists(g_repo, "mismatch_path", GIT_ENOTFOUND);
	/* note error code change, because add_setup made a repo in the workdir */
	refute_submodule_exists(g_repo, "sm_just_added", GIT_EEXISTS);
	refute_submodule_exists(g_repo, "sm_just_added_2", GIT_EEXISTS);
	/* these still exist in index and head respectively */
	assert_submodule_exists(g_repo, "sm_just_added_idx");
	assert_submodule_exists(g_repo, "sm_just_added_head");
	baseline_tests();

	{
		git_index *idx;
		cl_git_pass(git_repository_index(&idx, g_repo));
		cl_git_pass(git_index_remove_bypath(idx, "sm_just_added_idx"));
		cl_git_pass(git_index_remove_bypath(idx, "sm_just_added_head"));
		cl_git_pass(git_index_write(idx));
		git_index_free(idx);
	}

	refute_submodule_exists(g_repo, "sm_just_added_idx", GIT_EEXISTS);
	assert_submodule_exists(g_repo, "sm_just_added_head");

	{
		cl_git_pass(git_reference_create(NULL, g_repo, "refs/heads/master", git_reference_target(original_head), 1, "move head back"));
		git_reference_free(original_head);
	}

	refute_submodule_exists(g_repo, "sm_just_added_head", GIT_EEXISTS);
}