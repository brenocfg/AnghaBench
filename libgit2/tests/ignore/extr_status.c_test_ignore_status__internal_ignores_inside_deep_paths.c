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
 int /*<<< orphan*/  assert_is_ignored (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_ignore_add_rule (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  refute_is_ignored (char*) ; 

void test_ignore_status__internal_ignores_inside_deep_paths(void)
{
	const char *add_me = "Debug\nthis/is/deep\npatterned*/dir\n";

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_git_pass(git_ignore_add_rule(g_repo, add_me));

	assert_is_ignored("Debug");
	assert_is_ignored("and/Debug");
	assert_is_ignored("really/Debug/this/file");
	assert_is_ignored("Debug/what/I/say");

	refute_is_ignored("and/NoDebug");
	refute_is_ignored("NoDebug/this");
	refute_is_ignored("please/NoDebug/this");

	assert_is_ignored("this/is/deep");
	/* pattern containing slash gets FNM_PATHNAME so all slashes must match */
	refute_is_ignored("and/this/is/deep");
	assert_is_ignored("this/is/deep/too");
	/* pattern containing slash gets FNM_PATHNAME so all slashes must match */
	refute_is_ignored("but/this/is/deep/and/ignored");

	refute_is_ignored("this/is/not/deep");
	refute_is_ignored("is/this/not/as/deep");
	refute_is_ignored("this/is/deepish");
	refute_is_ignored("xthis/is/deep");
}