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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_basic_dirs ; 
 int /*<<< orphan*/  git_futils_mkdir (char*,int,int) ; 
 int git_path_isdir (char*) ; 

void test_core_mkdir__basic(void)
{
	cl_set_cleanup(cleanup_basic_dirs, NULL);

	/* make a directory */
	cl_assert(!git_path_isdir("d0"));
	cl_git_pass(git_futils_mkdir("d0", 0755, 0));
	cl_assert(git_path_isdir("d0"));

	/* make a path */
	cl_assert(!git_path_isdir("d1"));
	cl_git_pass(git_futils_mkdir("d1/d1.1/d1.2", 0755, GIT_MKDIR_PATH));
	cl_assert(git_path_isdir("d1"));
	cl_assert(git_path_isdir("d1/d1.1"));
	cl_assert(git_path_isdir("d1/d1.1/d1.2"));

	/* make a dir exclusively */
	cl_assert(!git_path_isdir("d2"));
	cl_git_pass(git_futils_mkdir("d2", 0755, GIT_MKDIR_EXCL));
	cl_assert(git_path_isdir("d2"));

	/* make exclusive failure */
	cl_git_fail(git_futils_mkdir("d2", 0755, GIT_MKDIR_EXCL));

	/* make a path exclusively */
	cl_assert(!git_path_isdir("d3"));
	cl_git_pass(git_futils_mkdir("d3/d3.1/d3.2", 0755, GIT_MKDIR_PATH | GIT_MKDIR_EXCL));
	cl_assert(git_path_isdir("d3"));
	cl_assert(git_path_isdir("d3/d3.1/d3.2"));

	/* make exclusive path failure */
	cl_git_fail(git_futils_mkdir("d3/d3.1/d3.2", 0755, GIT_MKDIR_PATH | GIT_MKDIR_EXCL));
	/* ??? Should EXCL only apply to the last item in the path? */

	/* path with trailing slash? */
	cl_assert(!git_path_isdir("d4"));
	cl_git_pass(git_futils_mkdir("d4/d4.1/", 0755, GIT_MKDIR_PATH));
	cl_assert(git_path_isdir("d4/d4.1"));
}