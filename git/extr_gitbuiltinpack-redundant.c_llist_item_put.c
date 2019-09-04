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
 struct llist_item* free_nodes ; 

__attribute__((used)) static inline void llist_item_put(struct llist_item *item)
{
	item->next = free_nodes;
	free_nodes = item;
}