#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_prettify_dir (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_commondir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void assert_sm_valid(git_repository *parent, git_repository *child, const char *sm_name)
{
	git_buf expected = GIT_BUF_INIT, actual = GIT_BUF_INIT;

	/* assert working directory */
	cl_git_pass(git_buf_joinpath(&expected, git_repository_workdir(parent), sm_name));
	cl_git_pass(git_path_prettify_dir(&expected, expected.ptr, NULL));
	cl_git_pass(git_buf_sets(&actual, git_repository_workdir(child)));
	cl_git_pass(git_path_prettify_dir(&actual, actual.ptr, NULL));
	cl_assert_equal_s(expected.ptr, actual.ptr);

	git_buf_clear(&expected);
	git_buf_clear(&actual);

	/* assert common directory */
	cl_git_pass(git_buf_joinpath(&expected, git_repository_commondir(parent), "modules"));
	cl_git_pass(git_buf_joinpath(&expected, expected.ptr, sm_name));
	cl_git_pass(git_path_prettify_dir(&expected, expected.ptr, NULL));
	cl_git_pass(git_buf_sets(&actual, git_repository_commondir(child)));
	cl_git_pass(git_path_prettify_dir(&actual, actual.ptr, NULL));
	cl_assert_equal_s(expected.ptr, actual.ptr);

	/* assert git directory */
	cl_git_pass(git_buf_sets(&actual, git_repository_path(child)));
	cl_git_pass(git_path_prettify_dir(&actual, actual.ptr, NULL));
	cl_assert_equal_s(expected.ptr, actual.ptr);

	git_buf_dispose(&expected);
	git_buf_dispose(&actual);
}