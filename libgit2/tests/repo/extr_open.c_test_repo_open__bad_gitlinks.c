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

/* Variables and functions */
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open_ext (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_gitlink_dir (char*,char const*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_repo_open__bad_gitlinks(void)
{
	git_repository *repo;
	static const char *bad_links[] = {
		"garbage\n", "gitdir", "gitdir:\n", "gitdir: foobar",
		"gitdir: ../invalid", "gitdir: ../invalid2",
		"gitdir: ../attr/.git with extra stuff",
		NULL
	};
	const char **scan;

	cl_git_sandbox_init("attr");

	cl_git_pass(p_mkdir("invalid", 0777));
	cl_git_pass(git_futils_mkdir_r("invalid2/.git", 0777));

	for (scan = bad_links; *scan != NULL; scan++) {
		make_gitlink_dir("alternate", *scan);
		cl_git_fail(git_repository_open_ext(&repo, "alternate", 0, NULL));
	}

	git_futils_rmdir_r("invalid", NULL, GIT_RMDIR_REMOVE_FILES);
	git_futils_rmdir_r("invalid2", NULL, GIT_RMDIR_REMOVE_FILES);
}