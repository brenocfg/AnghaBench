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
 int /*<<< orphan*/  GIT_ATTR_IS_TRUE (char const*) ; 
 int /*<<< orphan*/  GIT_ATTR_IS_UNSPECIFIED (char const*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_get_many (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char const**) ; 

void test_attr_repo__get_many_in_place(void)
{
	const char *vals[4] = { "repoattr", "rootattr", "missingattr", "subattr" };

	/* it should be legal to look up values into the same array that has
	 * the attribute names, overwriting each name as the value is found.
	 */

	cl_git_pass(git_attr_get_many(vals, g_repo, 0, "sub/subdir_test1", 4, vals));

	cl_assert(GIT_ATTR_IS_TRUE(vals[0]));
	cl_assert(GIT_ATTR_IS_TRUE(vals[1]));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(vals[2]));
	cl_assert_equal_s("yes", vals[3]);
}