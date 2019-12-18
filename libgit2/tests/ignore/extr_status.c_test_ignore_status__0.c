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
 int /*<<< orphan*/  GIT_ATTR_FILE__FROM_FILE ; 
 int /*<<< orphan*/  assert_ignored (int,char const*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_cache__is_cached (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void test_ignore_status__0(void)
{
	struct {
		const char *path;
		int expected;
	} test_cases[] = {
		/* pattern "ign" from .gitignore */
		{ "file", 0 },
		{ "ign", 1 },
		{ "sub", 0 },
		{ "sub/file", 0 },
		{ "sub/ign", 1 },
		{ "sub/ign/file", 1 },
		{ "sub/ign/sub", 1 },
		{ "sub/ign/sub/file", 1 },
		{ "sub/sub", 0 },
		{ "sub/sub/file", 0 },
		{ "sub/sub/ign", 1 },
		{ "sub/sub/sub", 0 },
		/* pattern "dir/" from .gitignore */
		{ "dir", 1 },
		{ "dir/", 1 },
		{ "sub/dir", 1 },
		{ "sub/dir/", 1 },
		{ "sub/dir/file", 1 }, /* contained in ignored parent */
		{ "sub/sub/dir", 0 }, /* dir is not actually a dir, but a file */
		{ NULL, 0 }
	}, *one_test;

	g_repo = cl_git_sandbox_init("attr");

	for (one_test = test_cases; one_test->path != NULL; one_test++)
		assert_ignored(one_test->expected, one_test->path);

	/* confirm that ignore files were cached */
	cl_assert(git_attr_cache__is_cached(
		g_repo, GIT_ATTR_FILE__FROM_FILE, ".git/info/exclude"));
	cl_assert(git_attr_cache__is_cached(
		g_repo, GIT_ATTR_FILE__FROM_FILE, ".gitignore"));
}