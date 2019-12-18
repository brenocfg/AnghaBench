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
 int /*<<< orphan*/  cl_assert_equal_p (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_attr_macro__macros_in_subdir_do_not_apply(void)
{
	const char *value;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_pass(p_mkdir("empty_standard_repo/dir", 0777));
	cl_git_rewritefile("empty_standard_repo/dir/.gitattributes",
			   "[attr]customattr key=value\n"
			   "file customattr\n");

	/* This should _not_ pass, as macros in subdirectories shall be ignored */
	cl_git_pass(git_attr_get(&value, g_repo, 0, "dir/file", "key"));
	cl_assert_equal_p(value, NULL);
}