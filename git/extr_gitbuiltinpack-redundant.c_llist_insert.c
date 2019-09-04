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
struct object_id {int dummy; } ;
struct llist_item {struct llist_item* next; struct object_id const* oid; } ;
struct llist {scalar_t__ size; struct llist_item* front; struct llist_item* back; } ;

/* Variables and functions */
 struct llist_item* llist_item_get () ; 

__attribute__((used)) static inline struct llist_item *llist_insert(struct llist *list,
					      struct llist_item *after,
					      const struct object_id *oid)
{
	struct llist_item *new_item = llist_item_get();
	new_item->oid = oid;
	new_item->next = NULL;

	if (after != NULL) {
		new_item->next = after->next;
		after->next = new_item;
		if (after == list->back)
			list->back = new_item;
	} else {/* insert in front */
		if (list->size == 0)
			list->back = new_item;
		else
			new_item->next = list->front;
		list->front = new_item;
	}
	list->size++;
	return new_item;
}