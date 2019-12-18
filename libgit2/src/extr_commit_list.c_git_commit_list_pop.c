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
typedef  int /*<<< orphan*/  git_commit_list_node ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * item; } ;
typedef  TYPE_1__ git_commit_list ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

git_commit_list_node *git_commit_list_pop(git_commit_list **stack)
{
	git_commit_list *top = *stack;
	git_commit_list_node *item = top ? top->item : NULL;

	if (top) {
		*stack = top->next;
		git__free(top);
	}
	return item;
}