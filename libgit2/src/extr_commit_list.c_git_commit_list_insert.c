#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_commit_list_node ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/ * item; } ;
typedef  TYPE_1__ git_commit_list ;

/* Variables and functions */
 TYPE_1__* git__malloc (int) ; 

git_commit_list *git_commit_list_insert(git_commit_list_node *item, git_commit_list **list_p)
{
	git_commit_list *new_list = git__malloc(sizeof(git_commit_list));
	if (new_list != NULL) {
		new_list->item = item;
		new_list->next = *list_p;
	}
	*list_p = new_list;
	return new_list;
}