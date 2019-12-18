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
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_get_many (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char const**) ; 

void test_attr_macro__bad_macros(void)
{
	const char *names[6] = { "rootattr", "positive", "negative",
		"firstmacro", "secondmacro", "thirdmacro" };
	const char *values[6];

	g_repo = cl_git_sandbox_init("attr");

	cl_git_pass(git_attr_get_many(values, g_repo, 0, "macro_bad", 6, names));

	/* these three just confirm that the "mymacro" rule ran */
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(values[0]));
	cl_assert(GIT_ATTR_IS_TRUE(values[1]));
	cl_assert(GIT_ATTR_IS_FALSE(values[2]));

	/* file contains:
	 *     # let's try some malicious macro defs
	 *     [attr]firstmacro -thirdmacro -secondmacro
	 *     [attr]secondmacro firstmacro -firstmacro
	 *     [attr]thirdmacro secondmacro=hahaha -firstmacro
	 *     macro_bad firstmacro secondmacro thirdmacro
	 *
	 * firstmacro assignment list ends up with:
	 *     -thirdmacro -secondmacro
	 * secondmacro assignment list expands "firstmacro" and ends up with:
	 *     -thirdmacro -secondmacro -firstmacro
	 * thirdmacro assignment don't expand so list ends up with:
	 *     secondmacro="hahaha"
	 *
	 * macro_bad assignment list ends up with:
	 *     -thirdmacro -secondmacro firstmacro &&
	 *     -thirdmacro -secondmacro -firstmacro secondmacro &&
	 *     secondmacro="hahaha" thirdmacro
	 *
	 * so summary results should be:
	 *     -firstmacro secondmacro="hahaha" thirdmacro
	 */
	cl_assert(GIT_ATTR_IS_FALSE(values[3]));
	cl_assert_equal_s("hahaha", values[4]);
	cl_assert(GIT_ATTR_IS_TRUE(values[5]));
}