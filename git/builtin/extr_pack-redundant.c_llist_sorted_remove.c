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
struct llist_item {struct llist_item* next; int /*<<< orphan*/  oid; } ;
struct llist {int /*<<< orphan*/  size; struct llist_item* back; struct llist_item* front; } ;

/* Variables and functions */
 int /*<<< orphan*/  llist_item_put (struct llist_item*) ; 
 int oidcmp (int /*<<< orphan*/ ,struct object_id const*) ; 

__attribute__((used)) static inline struct llist_item * llist_sorted_remove(struct llist *list, const struct object_id *oid, struct llist_item *hint)
{
	struct llist_item *prev, *l;

redo_from_start:
	l = (hint == NULL) ? list->front : hint;
	prev = NULL;
	while (l) {
		const int cmp = oidcmp(l->oid, oid);
		if (cmp > 0) /* not in list, since sorted */
			return prev;
		if (!cmp) { /* found */
			if (prev == NULL) {
				if (hint != NULL && hint != list->front) {
					/* we don't know the previous element */
					hint = NULL;
					goto redo_from_start;
				}
				list->front = l->next;
			} else
				prev->next = l->next;
			if (l == list->back)
				list->back = prev;
			llist_item_put(l);
			list->size--;
			return prev;
		}
		prev = l;
		l = l->next;
	}
	return prev;
}