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
union ring_state {scalar_t__ flags; scalar_t__ pidx_head; scalar_t__ pidx_tail; scalar_t__ cidx; int /*<<< orphan*/  state; } ;
struct mp_ring {scalar_t__ (* can_drain ) (struct mp_ring*) ;int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ BUSY ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ STALLED ; 
 int /*<<< orphan*/  atomic_cmpset_acq_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drain_ring (struct mp_ring*,union ring_state,scalar_t__,int) ; 
 scalar_t__ stub1 (struct mp_ring*) ; 

void
mp_ring_check_drainage(struct mp_ring *r, int budget)
{
	union ring_state os, ns;

	os.state = r->state;
	if (os.flags != STALLED || os.pidx_head != os.pidx_tail ||
	    r->can_drain(r) == 0)
		return;

	MPASS(os.cidx != os.pidx_tail);	/* implied by STALLED */
	ns.state = os.state;
	ns.flags = BUSY;

	/*
	 * The acquire style atomic guarantees visibility of items associated
	 * with the pidx that we read here.
	 */
	if (!atomic_cmpset_acq_64(&r->state, os.state, ns.state))
		return;

	drain_ring(r, ns, os.flags, budget);
}