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
typedef  int /*<<< orphan*/  git_repository_init_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_repository (char*) ; 
 int /*<<< orphan*/  git__suffixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ ) ; 
 int git_repository_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 

void test_repo_init__extended_0(void)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;

	/* without MKDIR this should fail */
	cl_git_fail(git_repository_init_ext(&_repo, "extended", &opts));

	/* make the directory first, then it should succeed */
	cl_git_pass(git_futils_mkdir("extended", 0775, 0));
	cl_git_pass(git_repository_init_ext(&_repo, "extended", &opts));

	cl_assert(!git__suffixcmp(git_repository_workdir(_repo), "/extended/"));
	cl_assert(!git__suffixcmp(git_repository_path(_repo), "/extended/.git/"));
	cl_assert(!git_repository_is_bare(_repo));
	cl_assert(git_repository_is_empty(_repo));

	cleanup_repository("extended");
}