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
struct addrnode {struct addrnode* next; struct addrnode* prev; } ;

/* Variables and functions */

__attribute__((used)) static void
lru_push(struct addrtree *tree, struct addrnode *node)
{
	if (!tree->first) {
		tree->first = node;
		node->prev = NULL;
	} else {
		tree->last->next = node;
		node->prev = tree->last;
	}
	tree->last = node;
	node->next = NULL;
}