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
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int cl_is_chmod_supported () ; 
 int cl_repo_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_repository ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 

void test_repo_init__reinit_overwrites_filemode(void)
{
	int expected = cl_is_chmod_supported(), current_value;

	/* Init a new repo */
	cl_set_cleanup(&cleanup_repository, "overwrite.git");
	cl_git_pass(git_repository_init(&_repo, "overwrite.git", 1));

	/* Change the "core.filemode" config value to something unlikely */
	cl_repo_set_bool(_repo, "core.filemode", !expected);

	git_repository_free(_repo);
	_repo = NULL;

	/* Reinit the repository */
	cl_git_pass(git_repository_init(&_repo, "overwrite.git", 1));

	/* Ensure the "core.filemode" config value has been reset */
	current_value = cl_repo_get_bool(_repo, "core.filemode");
	cl_assert_equal_i(expected, current_value);
}