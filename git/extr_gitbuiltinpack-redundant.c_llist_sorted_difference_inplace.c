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
struct llist {struct llist_item* front; } ;

/* Variables and functions */
 struct llist_item* llist_sorted_remove (struct llist*,int /*<<< orphan*/ ,struct llist_item*) ; 

__attribute__((used)) static void llist_sorted_difference_inplace(struct llist *A,
				     struct llist *B)
{
	struct llist_item *hint, *b;

	hint = NULL;
	b = B->front;

	while (b) {
		hint = llist_sorted_remove(A, b->oid, hint);
		b = b->next;
	}
}