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
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_attr_cache_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refute_is_ignored (char*) ; 

void test_ignore_status__1(void)
{
	g_repo = cl_git_sandbox_init("attr");

	cl_git_rewritefile("attr/.gitignore", "/*.txt\n/dir/\n");
	git_attr_cache_flush(g_repo);

	assert_is_ignored("root_test4.txt");
	refute_is_ignored("sub/subdir_test2.txt");
	assert_is_ignored("dir");
	assert_is_ignored("dir/");
	refute_is_ignored("sub/dir");
	refute_is_ignored("sub/dir/");
}