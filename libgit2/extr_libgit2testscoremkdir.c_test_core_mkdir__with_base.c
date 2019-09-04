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
 int GIT_MKDIR_EXCL ; 
 int GIT_MKDIR_PATH ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_basedir ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int) ; 
 int /*<<< orphan*/  git_futils_mkdir_relative (char*,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 

void test_core_mkdir__with_base(void)
{
#define BASEDIR "base/dir/here"

	cl_set_cleanup(cleanup_basedir, NULL);

	cl_git_pass(git_futils_mkdir(BASEDIR, 0755, GIT_MKDIR_PATH));

	cl_git_pass(git_futils_mkdir_relative("a", BASEDIR, 0755, 0, NULL));
	cl_assert(git_path_isdir(BASEDIR "/a"));

	cl_git_pass(git_futils_mkdir_relative("b/b1/b2", BASEDIR, 0755, GIT_MKDIR_PATH, NULL));
	cl_assert(git_path_isdir(BASEDIR "/b/b1/b2"));

	/* exclusive with existing base */
	cl_git_pass(git_futils_mkdir_relative("c/c1/c2", BASEDIR, 0755, GIT_MKDIR_PATH | GIT_MKDIR_EXCL, NULL));

	/* fail: exclusive with duplicated suffix */
	cl_git_fail(git_futils_mkdir_relative("c/c1/c3", BASEDIR, 0755, GIT_MKDIR_PATH | GIT_MKDIR_EXCL, NULL));

	/* fail: exclusive with any duplicated component */
	cl_git_fail(git_futils_mkdir_relative("c/cz/cz", BASEDIR, 0755, GIT_MKDIR_PATH | GIT_MKDIR_EXCL, NULL));

	/* success: exclusive without path */
	cl_git_pass(git_futils_mkdir_relative("c/c1/c3", BASEDIR, 0755, GIT_MKDIR_EXCL, NULL));

	/* path with shorter base and existing dirs */
	cl_git_pass(git_futils_mkdir_relative("dir/here/d/", "base", 0755, GIT_MKDIR_PATH, NULL));
	cl_assert(git_path_isdir("base/dir/here/d"));

	/* fail: path with shorter base and existing dirs */
	cl_git_fail(git_futils_mkdir_relative("dir/here/e/", "base", 0755, GIT_MKDIR_PATH | GIT_MKDIR_EXCL, NULL));

	/* fail: base with missing components */
	cl_git_fail(git_futils_mkdir_relative("f/", "base/missing", 0755, GIT_MKDIR_PATH, NULL));

	/* success: shift missing component to path */
	cl_git_pass(git_futils_mkdir_relative("missing/f/", "base/", 0755, GIT_MKDIR_PATH, NULL));
}