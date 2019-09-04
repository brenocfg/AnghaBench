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
struct commit_list {struct commit_list* next; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 struct commit_list** commit_list_append (int /*<<< orphan*/ ,struct commit_list**) ; 

struct commit_list *copy_commit_list(struct commit_list *list)
{
	struct commit_list *head = NULL;
	struct commit_list **pp = &head;
	while (list) {
		pp = commit_list_append(list->item, pp);
		list = list->next;
	}
	return head;
}