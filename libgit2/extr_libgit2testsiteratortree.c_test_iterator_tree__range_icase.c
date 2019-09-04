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
 int /*<<< orphan*/  check_tree_range (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 

void test_iterator_tree__range_icase(void)
{
	g_repo = cl_git_sandbox_init("testrepo");

	check_tree_range(g_repo, "B", "C", false, 0);
	check_tree_range(g_repo, "B", "C", true, 1);
	check_tree_range(g_repo, "b", "c", false, 1);
	check_tree_range(g_repo, "b", "c", true, 1);

	check_tree_range(g_repo, "a", "z", false, 3);
	check_tree_range(g_repo, "a", "z", true, 4);
	check_tree_range(g_repo, "A", "Z", false, 1);
	check_tree_range(g_repo, "A", "Z", true, 4);
	check_tree_range(g_repo, "a", "Z", false, 0);
	check_tree_range(g_repo, "a", "Z", true, 4);
	check_tree_range(g_repo, "A", "z", false, 4);
	check_tree_range(g_repo, "A", "z", true, 4);

	check_tree_range(g_repo, "new.txt", "new.txt", true, 1);
	check_tree_range(g_repo, "new.txt", "new.txt", false, 1);
	check_tree_range(g_repo, "README", "README", true, 1);
	check_tree_range(g_repo, "README", "README", false, 1);
}