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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path_isfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_rename (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_fake_stash_reference_and_reflog(git_repository *repo)
{
	git_reference *master, *new_master;
	git_buf log_path = GIT_BUF_INIT;

	git_buf_joinpath(&log_path, git_repository_path(repo), "logs/refs/fakestash");

	cl_assert_equal_i(false, git_path_isfile(git_buf_cstr(&log_path)));

	cl_git_pass(git_reference_lookup(&master, repo, "refs/heads/master"));
	cl_git_pass(git_reference_rename(&new_master, master, "refs/fakestash", 0, NULL));
	git_reference_free(master);

	cl_assert_equal_i(true, git_path_isfile(git_buf_cstr(&log_path)));

	git_buf_dispose(&log_path);
	git_reference_free(new_master);
}