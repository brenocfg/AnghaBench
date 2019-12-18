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
typedef  int /*<<< orphan*/  git_blame_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BLAME_OPTIONS_INIT ; 
 int /*<<< orphan*/  check_blame_hunk_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_blame ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blame_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blame_get_hunk_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_blame_simple__can_blame_huge_file(void)
{
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;

	cl_git_pass(git_repository_open(&g_repo, cl_fixture("blametest.git")));

	cl_git_pass(git_blame_file(&g_blame, g_repo, "huge.txt", &opts));
	cl_assert_equal_i(2, git_blame_get_hunk_count(g_blame));
	check_blame_hunk_index(g_repo, g_blame, 0, 1,     65536, 0, "4eecfea", "huge.txt");
	check_blame_hunk_index(g_repo, g_blame, 1, 65537, 1,     0, "6653ff4", "huge.txt");
}