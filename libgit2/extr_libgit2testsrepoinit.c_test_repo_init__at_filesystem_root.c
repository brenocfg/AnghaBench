#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 char* clar_sandbox_path () ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 
 int git_path_isdir (int /*<<< orphan*/ ) ; 
 int git_path_root (char const*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_repo_init__at_filesystem_root(void)
{
	git_repository *repo;
	const char *sandbox = clar_sandbox_path();
	git_buf root = GIT_BUF_INIT;
	int root_len;

	if (!cl_is_env_set("GITTEST_INVASIVE_FS_STRUCTURE"))
		cl_skip();

	root_len = git_path_root(sandbox);
	cl_assert(root_len >= 0);

	git_buf_put(&root, sandbox, root_len+1);
	git_buf_joinpath(&root, root.ptr, "libgit2_test_dir");

	cl_assert(!git_path_exists(root.ptr));

	cl_git_pass(git_repository_init(&repo, root.ptr, 0));
	cl_assert(git_path_isdir(root.ptr));
	cl_git_pass(git_futils_rmdir_r(root.ptr, NULL, GIT_RMDIR_REMOVE_FILES));

	git_buf_dispose(&root);
	git_repository_free(repo);
}