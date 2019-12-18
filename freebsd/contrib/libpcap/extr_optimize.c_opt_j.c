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
struct edge {int* edom; struct block* succ; int /*<<< orphan*/  pred; } ;
struct TYPE_4__ {struct block* succ; } ;
struct block {TYPE_1__ et; } ;
struct TYPE_5__ {int edgewords; scalar_t__ done; int /*<<< orphan*/ * edges; } ;
typedef  TYPE_2__ opt_state_t ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 scalar_t__ JF (struct block*) ; 
 scalar_t__ JT (struct block*) ; 
 struct block* fold_edge (struct block*,int /*<<< orphan*/ ) ; 
 int lowest_set_bit (int) ; 
 int /*<<< orphan*/  use_conflict (int /*<<< orphan*/ ,struct block*) ; 

__attribute__((used)) static void
opt_j(opt_state_t *opt_state, struct edge *ep)
{
	register int i, k;
	register struct block *target;

	if (JT(ep->succ) == 0)
		return;

	if (JT(ep->succ) == JF(ep->succ)) {
		/*
		 * Common branch targets can be eliminated, provided
		 * there is no data dependency.
		 */
		if (!use_conflict(ep->pred, ep->succ->et.succ)) {
			opt_state->done = 0;
			ep->succ = JT(ep->succ);
		}
	}
	/*
	 * For each edge dominator that matches the successor of this
	 * edge, promote the edge successor to the its grandchild.
	 *
	 * XXX We violate the set abstraction here in favor a reasonably
	 * efficient loop.
	 */
 top:
	for (i = 0; i < opt_state->edgewords; ++i) {
		register bpf_u_int32 x = ep->edom[i];

		while (x != 0) {
			k = lowest_set_bit(x);
			x &=~ (1 << k);
			k += i * BITS_PER_WORD;

			target = fold_edge(ep->succ, opt_state->edges[k]);
			/*
			 * Check that there is no data dependency between
			 * nodes that will be violated if we move the edge.
			 */
			if (target != 0 && !use_conflict(ep->pred, target)) {
				opt_state->done = 0;
				ep->succ = target;
				if (JT(target) != 0)
					/*
					 * Start over unless we hit a leaf.
					 */
					goto top;
				return;
			}
		}
	}
}