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
union ring_state {scalar_t__ state; scalar_t__ flags; scalar_t__ pidx_head; scalar_t__ pidx_tail; scalar_t__ cidx; } ;
struct ifmp_ring {scalar_t__ state; scalar_t__ (* can_drain ) (struct ifmp_ring*) ;int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ ABDICATED ; 
 scalar_t__ BUSY ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ STALLED ; 
 int /*<<< orphan*/  atomic_cmpset_acq_64 (scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  drain_ring_locked (struct ifmp_ring*,union ring_state,scalar_t__,int) ; 
 int /*<<< orphan*/  drain_ring_lockless (struct ifmp_ring*,union ring_state,scalar_t__,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct ifmp_ring*) ; 

void
ifmp_ring_check_drainage(struct ifmp_ring *r, int budget)
{
	union ring_state os, ns;

	os.state = r->state;
	if ((os.flags != STALLED && os.flags != ABDICATED) ||	// Only continue in STALLED and ABDICATED
	    os.pidx_head != os.pidx_tail ||			// Require work to be available
	    (os.flags != ABDICATED && r->can_drain(r) == 0))	// Can either drain, or everyone left
		return;

	MPASS(os.cidx != os.pidx_tail);	/* implied by STALLED */
	ns.state = os.state;
	ns.flags = BUSY;


#ifdef MP_RING_NO_64BIT_ATOMICS
	mtx_lock(&r->lock);
	if (r->state != os.state) {
		mtx_unlock(&r->lock);
		return;
	}
	r->state = ns.state;
	drain_ring_locked(r, ns, os.flags, budget);
	mtx_unlock(&r->lock);
#else
	/*
	 * The acquire style atomic guarantees visibility of items associated
	 * with the pidx that we read here.
	 */
	if (!atomic_cmpset_acq_64(&r->state, os.state, ns.state))
		return;


	drain_ring_lockless(r, ns, os.flags, budget);
#endif
}