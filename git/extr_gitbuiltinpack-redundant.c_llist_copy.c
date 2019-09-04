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
struct llist_item {struct llist_item* next; int /*<<< orphan*/  oid; } ;
struct llist {struct llist_item* back; struct llist_item* front; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  llist_init (struct llist**) ; 
 void* llist_item_get () ; 

__attribute__((used)) static struct llist * llist_copy(struct llist *list)
{
	struct llist *ret;
	struct llist_item *new_item, *old_item, *prev;

	llist_init(&ret);

	if ((ret->size = list->size) == 0)
		return ret;

	new_item = ret->front = llist_item_get();
	new_item->oid = list->front->oid;

	old_item = list->front->next;
	while (old_item) {
		prev = new_item;
		new_item = llist_item_get();
		prev->next = new_item;
		new_item->oid = old_item->oid;
		old_item = old_item->next;
	}
	new_item->next = NULL;
	ret->back = new_item;

	return ret;
}