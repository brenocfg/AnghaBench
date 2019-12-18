#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roff_node {struct roff_node* prev; struct roff_node* parent; struct roff_node* last; struct roff_node* next; struct roff_node* child; } ;
struct TYPE_2__ {struct roff_node* first; } ;
struct roff_man {TYPE_1__ meta; int /*<<< orphan*/  next; struct roff_node* last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROFF_NEXT_CHILD ; 
 int /*<<< orphan*/  ROFF_NEXT_SIBLING ; 

void
roff_node_unlink(struct roff_man *man, struct roff_node *n)
{

	/* Adjust siblings. */

	if (n->prev)
		n->prev->next = n->next;
	if (n->next)
		n->next->prev = n->prev;

	/* Adjust parent. */

	if (n->parent != NULL) {
		if (n->parent->child == n)
			n->parent->child = n->next;
		if (n->parent->last == n)
			n->parent->last = n->prev;
	}

	/* Adjust parse point. */

	if (man == NULL)
		return;
	if (man->last == n) {
		if (n->prev == NULL) {
			man->last = n->parent;
			man->next = ROFF_NEXT_CHILD;
		} else {
			man->last = n->prev;
			man->next = ROFF_NEXT_SIBLING;
		}
	}
	if (man->meta.first == n)
		man->meta.first = NULL;
}