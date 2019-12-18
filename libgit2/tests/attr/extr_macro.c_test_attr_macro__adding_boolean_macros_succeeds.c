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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_add_macro (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

void test_attr_macro__adding_boolean_macros_succeeds(void)
{
	const char *value;

	g_repo = cl_git_sandbox_init("empty_standard_repo");
	cl_git_pass(git_attr_add_macro(g_repo, "macro-pos", "positive"));
	cl_git_pass(git_attr_add_macro(g_repo, "macro-neg", "-negative"));
	cl_git_rewritefile("empty_standard_repo/.gitattributes", "file.txt macro-pos macro-neg\n");

	cl_git_pass(git_attr_get(&value, g_repo, 0, "file.txt", "positive"));
	cl_assert(GIT_ATTR_IS_TRUE(value));
	cl_git_pass(git_attr_get(&value, g_repo, 0, "file.txt", "negative"));
	cl_assert(GIT_ATTR_IS_FALSE(value));
}