#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* next; } ;
struct TYPE_16__ {TYPE_1__ x; } ;
struct TYPE_15__ {unsigned int mask; size_t set; int /*<<< orphan*/ * vbl; } ;
struct TYPE_13__ {TYPE_4__* regnode; scalar_t__ lastuse; TYPE_3__** wildcard; } ;
struct TYPE_14__ {TYPE_2__ x; } ;
typedef  TYPE_3__* Symbol ;
typedef  TYPE_4__* Regnode ;
typedef  TYPE_5__* Node ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 unsigned int* tmask ; 
 int /*<<< orphan*/  uses (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static Symbol spillee(Symbol set, unsigned mask[], Node here) {
	Symbol bestreg = NULL;
	int bestdist = -1, i;

	assert(set);
	if (!set->x.wildcard)
		bestreg = set;
	else {
		for (i = 31; i >= 0; i--) {
			Symbol ri = set->x.wildcard[i];
			if (
				ri != NULL &&
				ri->x.lastuse &&
				(ri->x.regnode->mask&tmask[ri->x.regnode->set]&mask[ri->x.regnode->set])
			) {
				Regnode rn = ri->x.regnode;
				Node q = here;
				int dist = 0;
				for (; q && !uses(q, rn); q = q->x.next)
					dist++;
				if (q && dist > bestdist) {
					bestdist = dist;
					bestreg = ri;
				}
			}
		}
	}
	assert(bestreg); /* Must be able to spill something. Reconfigure the register allocator
		to ensure that we can allocate a register for all nodes without spilling
		the node's necessary input regs. */	
	assert(bestreg->x.regnode->vbl == NULL); /* Can't spill register variables because
		the reload site might be in other blocks. Reconfigure the register allocator
		to ensure that this register is never allocated to a variable. */
	return bestreg;
}