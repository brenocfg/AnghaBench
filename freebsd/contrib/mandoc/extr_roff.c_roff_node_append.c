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
struct roff_node {int type; struct roff_node* parent; int /*<<< orphan*/  norm; struct roff_node* tail; struct roff_node* body; int /*<<< orphan*/  end; struct roff_node* head; struct roff_node* child; struct roff_node* last; struct roff_node* prev; struct roff_node* next; } ;
struct roff_man {int next; struct roff_node* last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDBODY_NOT ; 
 scalar_t__ ROFFT_BLOCK ; 
#define  ROFFT_BODY 132 
#define  ROFFT_HEAD 131 
#define  ROFFT_TAIL 130 
#define  ROFF_NEXT_CHILD 129 
#define  ROFF_NEXT_SIBLING 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 

void
roff_node_append(struct roff_man *man, struct roff_node *n)
{

	switch (man->next) {
	case ROFF_NEXT_SIBLING:
		if (man->last->next != NULL) {
			n->next = man->last->next;
			man->last->next->prev = n;
		} else
			man->last->parent->last = n;
		man->last->next = n;
		n->prev = man->last;
		n->parent = man->last->parent;
		break;
	case ROFF_NEXT_CHILD:
		if (man->last->child != NULL) {
			n->next = man->last->child;
			man->last->child->prev = n;
		} else
			man->last->last = n;
		man->last->child = n;
		n->parent = man->last;
		break;
	default:
		abort();
	}
	man->last = n;

	switch (n->type) {
	case ROFFT_HEAD:
		n->parent->head = n;
		break;
	case ROFFT_BODY:
		if (n->end != ENDBODY_NOT)
			return;
		n->parent->body = n;
		break;
	case ROFFT_TAIL:
		n->parent->tail = n;
		break;
	default:
		return;
	}

	/*
	 * Copy over the normalised-data pointer of our parent.  Not
	 * everybody has one, but copying a null pointer is fine.
	 */

	n->norm = n->parent->norm;
	assert(n->parent->type == ROFFT_BLOCK);
}