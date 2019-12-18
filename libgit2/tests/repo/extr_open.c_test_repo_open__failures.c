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
struct TYPE_6__ {int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_REPOSITORY_OPEN_NO_DOTGIT ; 
 int GIT_REPOSITORY_OPEN_NO_SEARCH ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_repository_open_ext (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_repo_open__failures(void)
{
	git_repository *base, *repo;
	git_buf ceiling = GIT_BUF_INIT;

	base = cl_git_sandbox_init("attr");
	cl_git_pass(git_buf_sets(&ceiling, git_repository_workdir(base)));

	/* fail with no searching */
	cl_git_fail(git_repository_open(&repo, "attr/sub"));
	cl_git_fail(git_repository_open_ext(
		&repo, "attr/sub", GIT_REPOSITORY_OPEN_NO_SEARCH, NULL));

	/* fail with ceiling too low */
	cl_git_fail(git_repository_open_ext(&repo, "attr/sub", 0, ceiling.ptr));
	cl_git_pass(git_buf_joinpath(&ceiling, ceiling.ptr, "sub"));
	cl_git_fail(git_repository_open_ext(&repo, "attr/sub/sub", 0, ceiling.ptr));

	/* fail with no repo */
	cl_git_pass(p_mkdir("alternate", 0777));
	cl_git_pass(p_mkdir("alternate/.git", 0777));
	cl_git_fail(git_repository_open_ext(&repo, "alternate", 0, NULL));
	cl_git_fail(git_repository_open_ext(&repo, "alternate/.git", 0, NULL));

	/* fail with no searching and no appending .git */
	cl_git_fail(git_repository_open_ext(
		&repo, "attr",
		GIT_REPOSITORY_OPEN_NO_SEARCH | GIT_REPOSITORY_OPEN_NO_DOTGIT,
		NULL));

	git_buf_dispose(&ceiling);
}