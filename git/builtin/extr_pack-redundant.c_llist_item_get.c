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
struct llist_item {struct llist_item* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct llist_item*,int) ; 
 int BLKSIZE ; 
 struct llist_item* free_nodes ; 
 int /*<<< orphan*/  llist_item_put (struct llist_item*) ; 

__attribute__((used)) static inline struct llist_item *llist_item_get(void)
{
	struct llist_item *new_item;
	if ( free_nodes ) {
		new_item = free_nodes;
		free_nodes = free_nodes->next;
	} else {
		int i = 1;
		ALLOC_ARRAY(new_item, BLKSIZE);
		for (; i < BLKSIZE; i++)
			llist_item_put(&new_item[i]);
	}
	return new_item;
}