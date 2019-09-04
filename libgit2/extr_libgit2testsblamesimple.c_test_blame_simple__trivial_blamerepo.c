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
 int /*<<< orphan*/  check_blame_hunk_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_blame ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_blame_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blame_get_hunk_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_blame_simple__trivial_blamerepo(void)
{
	cl_git_pass(git_repository_open(&g_repo, cl_fixture("blametest.git")));
	cl_git_pass(git_blame_file(&g_blame, g_repo, "b.txt", NULL));

	cl_assert_equal_i(4, git_blame_get_hunk_count(g_blame));
	check_blame_hunk_index(g_repo, g_blame, 0,  1, 4, 0, "da237394", "b.txt");
	check_blame_hunk_index(g_repo, g_blame, 1,  5, 1, 1, "b99f7ac0", "b.txt");
	check_blame_hunk_index(g_repo, g_blame, 2,  6, 5, 0, "63d671eb", "b.txt");
	check_blame_hunk_index(g_repo, g_blame, 3, 11, 5, 0, "aa06ecca", "b.txt");
}