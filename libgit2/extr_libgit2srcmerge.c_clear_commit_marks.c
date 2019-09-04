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
typedef  int /*<<< orphan*/  git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 int /*<<< orphan*/  clear_commit_marks_1 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  git_commit_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_commit_list_pop (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void clear_commit_marks(git_commit_list_node *commit, unsigned int mark)
{
	git_commit_list *list = NULL;
	git_commit_list_insert(commit, &list);
	while (list)
		clear_commit_marks_1(&list, git_commit_list_pop(&list), mark);
}