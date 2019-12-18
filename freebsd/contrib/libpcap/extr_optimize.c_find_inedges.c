#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct block {int level; int /*<<< orphan*/  ef; int /*<<< orphan*/  et; struct block* link; } ;
struct TYPE_5__ {int n_blocks; struct block** levels; TYPE_1__** blocks; } ;
typedef  TYPE_2__ opt_state_t ;
struct TYPE_4__ {scalar_t__ in_edges; } ;

/* Variables and functions */
 int /*<<< orphan*/  JF (struct block*) ; 
 int /*<<< orphan*/  JT (struct block*) ; 
 int /*<<< orphan*/  link_inedge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_inedges(opt_state_t *opt_state, struct block *root)
{
	int i;
	struct block *b;

	for (i = 0; i < opt_state->n_blocks; ++i)
		opt_state->blocks[i]->in_edges = 0;

	/*
	 * Traverse the graph, adding each edge to the predecessor
	 * list of its successors.  Skip the leaves (i.e. level 0).
	 */
	for (i = root->level; i > 0; --i) {
		for (b = opt_state->levels[i]; b != 0; b = b->link) {
			link_inedge(&b->et, JT(b));
			link_inedge(&b->ef, JF(b));
		}
	}
}