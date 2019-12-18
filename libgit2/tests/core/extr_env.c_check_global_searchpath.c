#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct TYPE_12__* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OPT_GET_SEARCH_PATH ; 
 int /*<<< orphan*/  GIT_OPT_SET_SEARCH_PATH ; 
 int /*<<< orphan*/  GIT_PATH_LIST_SEPARATOR ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git__prefixcmp (TYPE_1__*,char const*) ; 
 scalar_t__ git__suffixcmp (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_join (TYPE_1__*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_sysdir_find_global_file (TYPE_1__*,char const*) ; 

__attribute__((used)) static void check_global_searchpath(
	const char *path, int position, const char *file, git_buf *temp)
{
	git_buf out = GIT_BUF_INIT;

	/* build and set new path */
	if (position < 0)
		cl_git_pass(git_buf_join(temp, GIT_PATH_LIST_SEPARATOR, path, "$PATH"));
	else if (position > 0)
		cl_git_pass(git_buf_join(temp, GIT_PATH_LIST_SEPARATOR, "$PATH", path));
	else
		cl_git_pass(git_buf_sets(temp, path));

	cl_git_pass(git_libgit2_opts(
		GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, temp->ptr));

	/* get path and make sure $PATH expansion worked */
	cl_git_pass(git_libgit2_opts(
		GIT_OPT_GET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, &out));

	if (position < 0)
		cl_assert(git__prefixcmp(out.ptr, path) == 0);
	else if (position > 0)
		cl_assert(git__suffixcmp(out.ptr, path) == 0);
	else
		cl_assert_equal_s(out.ptr, path);

	/* find file using new path */
	cl_git_pass(git_sysdir_find_global_file(temp, file));

	/* reset path and confirm file not found */
	cl_git_pass(git_libgit2_opts(
		GIT_OPT_SET_SEARCH_PATH, GIT_CONFIG_LEVEL_GLOBAL, NULL));
	cl_assert_equal_i(
		GIT_ENOTFOUND, git_sysdir_find_global_file(temp, file));

	git_buf_dispose(&out);
}