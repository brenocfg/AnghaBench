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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  check_index_range (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

void test_iterator_index__range_icase(void)
{
	git_index *index;
	git_tree *head;

	g_repo = cl_git_sandbox_init("testrepo");

	/* reset index to match HEAD */
	cl_git_pass(git_repository_head_tree(&head, g_repo));
	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_read_tree(index, head));
	cl_git_pass(git_index_write(index));
	git_tree_free(head);
	git_index_free(index);

	/* do some ranged iterator checks toggling case sensitivity */
	check_index_range(g_repo, "B", "C", false, 0);
	check_index_range(g_repo, "B", "C", true, 1);
	check_index_range(g_repo, "a", "z", false, 3);
	check_index_range(g_repo, "a", "z", true, 4);
}