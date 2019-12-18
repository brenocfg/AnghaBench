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
 int /*<<< orphan*/  git_attr_get_many (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char const**) ; 

void test_attr_repo__get_many(void)
{
	const char *names[4] = { "repoattr", "rootattr", "missingattr", "subattr" };
	const char *values[4];

	cl_git_pass(git_attr_get_many(values, g_repo, 0, "root_test1", 4, names));

	cl_assert(GIT_ATTR_IS_TRUE(values[0]));
	cl_assert(GIT_ATTR_IS_TRUE(values[1]));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(values[2]));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(values[3]));

	cl_git_pass(git_attr_get_many(values, g_repo, 0, "root_test2", 4, names));

	cl_assert(GIT_ATTR_IS_TRUE(values[0]));
	cl_assert(GIT_ATTR_IS_FALSE(values[1]));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(values[2]));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(values[3]));

	cl_git_pass(git_attr_get_many(values, g_repo, 0, "sub/subdir_test1", 4, names));

	cl_assert(GIT_ATTR_IS_TRUE(values[0]));
	cl_assert(GIT_ATTR_IS_TRUE(values[1]));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(values[2]));
	cl_assert_equal_s("yes", values[3]);
}