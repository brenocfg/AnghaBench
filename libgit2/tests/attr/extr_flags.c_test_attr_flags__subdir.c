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
 int GIT_ATTR_CHECK_FILE_THEN_INDEX ; 
 int GIT_ATTR_CHECK_INDEX_THEN_FILE ; 
 int GIT_ATTR_CHECK_NO_SYSTEM ; 
 int /*<<< orphan*/  GIT_ATTR_IS_TRUE (char const*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ *,int,char*,char*) ; 

void test_attr_flags__subdir(void)
{
	git_repository *repo = cl_git_sandbox_init("attr_index");
	const char *value;

	/* wd then index */
	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_FILE_THEN_INDEX,
		"sub/sub/README.md", "bar"));
	cl_assert_equal_s(value, "1234");

	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_FILE_THEN_INDEX,
		"sub/sub/README.txt", "another"));
	cl_assert_equal_s(value, "one");

	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_FILE_THEN_INDEX,
		"sub/sub/README.txt", "again"));
	cl_assert(GIT_ATTR_IS_TRUE(value));

	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_FILE_THEN_INDEX,
		"sub/sub/README.txt", "beep"));
	cl_assert_equal_s(value, "10");

	/* index then wd */
	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_INDEX_THEN_FILE,
		"sub/sub/README.md", "bar"));
	cl_assert_equal_s(value, "1337");

	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_INDEX_THEN_FILE,
		"sub/sub/README.txt", "another"));
	cl_assert_equal_s(value, "one");

	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_INDEX_THEN_FILE,
		"sub/sub/README.txt", "again"));
	cl_assert(GIT_ATTR_IS_TRUE(value));

	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM | GIT_ATTR_CHECK_INDEX_THEN_FILE,
		"sub/sub/README.txt", "beep"));
	cl_assert_equal_s(value, "5");
}