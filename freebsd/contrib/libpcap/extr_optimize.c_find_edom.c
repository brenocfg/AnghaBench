#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int* uset ;
struct TYPE_6__ {int /*<<< orphan*/  edom; } ;
struct block {int level; TYPE_3__ ef; TYPE_3__ et; struct block* link; } ;
struct TYPE_5__ {int* all_edge_sets; int n_edges; int edgewords; struct block** levels; } ;
typedef  TYPE_1__ opt_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  propedom (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static void
find_edom(opt_state_t *opt_state, struct block *root)
{
	int i;
	uset x;
	struct block *b;

	x = opt_state->all_edge_sets;
	for (i = opt_state->n_edges * opt_state->edgewords; --i >= 0; )
		x[i] = 0xFFFFFFFFU;

	/* root->level is the highest level no found. */
	memset(root->et.edom, 0, opt_state->edgewords * sizeof(*(uset)0));
	memset(root->ef.edom, 0, opt_state->edgewords * sizeof(*(uset)0));
	for (i = root->level; i >= 0; --i) {
		for (b = opt_state->levels[i]; b != 0; b = b->link) {
			propedom(opt_state, &b->et);
			propedom(opt_state, &b->ef);
		}
	}
}