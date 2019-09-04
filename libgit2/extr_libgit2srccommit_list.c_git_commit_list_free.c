#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ git_commit_list ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

void git_commit_list_free(git_commit_list **list_p)
{
	git_commit_list *list = *list_p;

	if (list == NULL)
		return;

	while (list) {
		git_commit_list *temp = list;
		list = temp->next;
		git__free(temp);
	}

	*list_p = NULL;
}