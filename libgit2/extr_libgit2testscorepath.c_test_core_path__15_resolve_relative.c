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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert_resolve_relative (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_path_resolve_relative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_core_path__15_resolve_relative(void)
{
	git_buf buf = GIT_BUF_INIT;

	assert_resolve_relative(&buf, "", "");
	assert_resolve_relative(&buf, "", ".");
	assert_resolve_relative(&buf, "", "./");
	assert_resolve_relative(&buf, "..", "..");
	assert_resolve_relative(&buf, "../", "../");
	assert_resolve_relative(&buf, "..", "./..");
	assert_resolve_relative(&buf, "../", "./../");
	assert_resolve_relative(&buf, "../", "../.");
	assert_resolve_relative(&buf, "../", ".././");
	assert_resolve_relative(&buf, "../..", "../..");
	assert_resolve_relative(&buf, "../../", "../../");

	assert_resolve_relative(&buf, "/", "/");
	assert_resolve_relative(&buf, "/", "/.");

	assert_resolve_relative(&buf, "", "a/..");
	assert_resolve_relative(&buf, "", "a/../");
	assert_resolve_relative(&buf, "", "a/../.");

	assert_resolve_relative(&buf, "/a", "/a");
	assert_resolve_relative(&buf, "/a/", "/a/.");
	assert_resolve_relative(&buf, "/", "/a/../");
	assert_resolve_relative(&buf, "/", "/a/../.");
	assert_resolve_relative(&buf, "/", "/a/.././");

	assert_resolve_relative(&buf, "a", "a");
	assert_resolve_relative(&buf, "a/", "a/");
	assert_resolve_relative(&buf, "a/", "a/.");
	assert_resolve_relative(&buf, "a/", "a/./");

	assert_resolve_relative(&buf, "a/b", "a//b");
	assert_resolve_relative(&buf, "a/b/c", "a/b/c");
	assert_resolve_relative(&buf, "b/c", "./b/c");
	assert_resolve_relative(&buf, "a/c", "a/./c");
	assert_resolve_relative(&buf, "a/b/", "a/b/.");

	assert_resolve_relative(&buf, "/a/b/c", "///a/b/c");
	assert_resolve_relative(&buf, "/", "////");
	assert_resolve_relative(&buf, "/a", "///a");
	assert_resolve_relative(&buf, "/", "///.");
	assert_resolve_relative(&buf, "/", "///a/..");

	assert_resolve_relative(&buf, "../../path", "../../test//../././path");
	assert_resolve_relative(&buf, "../d", "a/b/../../../c/../d");

	cl_git_pass(git_buf_sets(&buf, "/.."));
	cl_git_fail(git_path_resolve_relative(&buf, 0));

	cl_git_pass(git_buf_sets(&buf, "/./.."));
	cl_git_fail(git_path_resolve_relative(&buf, 0));

	cl_git_pass(git_buf_sets(&buf, "/.//.."));
	cl_git_fail(git_path_resolve_relative(&buf, 0));

	cl_git_pass(git_buf_sets(&buf, "/../."));
	cl_git_fail(git_path_resolve_relative(&buf, 0));

	cl_git_pass(git_buf_sets(&buf, "/../.././../a"));
	cl_git_fail(git_path_resolve_relative(&buf, 0));

	cl_git_pass(git_buf_sets(&buf, "////.."));
	cl_git_fail(git_path_resolve_relative(&buf, 0));

	/* things that start with Windows network paths */
#ifdef GIT_WIN32
	assert_resolve_relative(&buf, "//a/b/c", "//a/b/c");
	assert_resolve_relative(&buf, "//a/", "//a/b/..");
	assert_resolve_relative(&buf, "//a/b/c", "//a/Q/../b/x/y/../../c");

	cl_git_pass(git_buf_sets(&buf, "//a/b/../.."));
	cl_git_fail(git_path_resolve_relative(&buf, 0));
#else
	assert_resolve_relative(&buf, "/a/b/c", "//a/b/c");
	assert_resolve_relative(&buf, "/a/", "//a/b/..");
	assert_resolve_relative(&buf, "/a/b/c", "//a/Q/../b/x/y/../../c");
	assert_resolve_relative(&buf, "/", "//a/b/../..");
#endif

	git_buf_dispose(&buf);
}