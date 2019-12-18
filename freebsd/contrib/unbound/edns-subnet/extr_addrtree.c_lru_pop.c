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
struct addrtree {struct addrnode* last; struct addrnode* first; } ;
struct addrnode {struct addrnode* prev; struct addrnode* next; } ;

/* Variables and functions */

__attribute__((used)) static void
lru_pop(struct addrtree *tree, struct addrnode *node)
{
	if (node == tree->first) {
		if (!node->next) { /* it is the last as well */
			tree->first = NULL;
			tree->last = NULL;
		} else {
			tree->first = node->next;
			tree->first->prev = NULL;
		}
	} else if (node == tree->last) { /* but not the first */
		tree->last = node->prev;
		tree->last->next = NULL;
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}