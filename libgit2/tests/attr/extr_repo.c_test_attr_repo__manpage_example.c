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
 int /*<<< orphan*/  GIT_ATTR_IS_FALSE (char const*) ; 
 int /*<<< orphan*/  GIT_ATTR_IS_TRUE (char const*) ; 
 int /*<<< orphan*/  GIT_ATTR_IS_UNSPECIFIED (char const*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

void test_attr_repo__manpage_example(void)
{
	const char *value;

	cl_git_pass(git_attr_get(&value, g_repo, 0, "sub/abc", "foo"));
	cl_assert(GIT_ATTR_IS_TRUE(value));

	cl_git_pass(git_attr_get(&value, g_repo, 0, "sub/abc", "bar"));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(value));

	cl_git_pass(git_attr_get(&value, g_repo, 0, "sub/abc", "baz"));
	cl_assert(GIT_ATTR_IS_FALSE(value));

	cl_git_pass(git_attr_get(&value, g_repo, 0, "sub/abc", "merge"));
	cl_assert_equal_s("filfre", value);

	cl_git_pass(git_attr_get(&value, g_repo, 0, "sub/abc", "frotz"));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(value));
}