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
struct eqn_node {int /*<<< orphan*/  gsize; } ;
struct eqn_box {struct eqn_box* last; struct eqn_box* first; struct eqn_box* prev; struct eqn_box* next; int /*<<< orphan*/  size; int /*<<< orphan*/  font; struct eqn_box* parent; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct eqn_box* eqn_box_new () ; 

__attribute__((used)) static struct eqn_box *
eqn_box_alloc(struct eqn_node *ep, struct eqn_box *parent)
{
	struct eqn_box	*bp;

	bp = eqn_box_new();
	bp->parent = parent;
	bp->parent->args++;
	bp->font = bp->parent->font;
	bp->size = ep->gsize;

	if (NULL != parent->first) {
		parent->last->next = bp;
		bp->prev = parent->last;
	} else
		parent->first = bp;

	parent->last = bp;
	return bp;
}