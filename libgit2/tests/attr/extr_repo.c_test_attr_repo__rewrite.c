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
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

void test_attr_repo__rewrite(void)
{
	const char *value;

	cl_git_rewritefile("attr/.gitattributes", "file.txt foo=first\n");
	cl_git_pass(git_attr_get(&value, g_repo, 0, "file.txt", "foo"));
	cl_assert_equal_s(value, "first");

	cl_git_rewritefile("attr/.gitattributes", "file.txt foo=second\n");
	cl_git_pass(git_attr_get(&value, g_repo, 0, "file.txt", "foo"));
	cl_assert_equal_s(value, "second");

	cl_git_rewritefile("attr/.gitattributes", "file.txt other=value\n");
	cl_git_pass(git_attr_get(&value, g_repo, 0, "file.txt", "foo"));
	cl_assert_equal_p(value, NULL);
}