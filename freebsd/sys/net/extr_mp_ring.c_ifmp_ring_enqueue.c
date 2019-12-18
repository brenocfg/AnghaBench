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
union ring_state {scalar_t__ flags; int pidx_head; int pidx_tail; int /*<<< orphan*/  state; } ;
typedef  int uint16_t ;
struct ifmp_ring {int size; int /*<<< orphan*/  enqueues; int /*<<< orphan*/  state; int /*<<< orphan*/ * items; int /*<<< orphan*/  drops; } ;

/* Variables and functions */
 scalar_t__ ABDICATED ; 
 scalar_t__ BUSY ; 
 int ENOBUFS ; 
 scalar_t__ IDLE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ STALLED ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ atomic_fcmpset_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_fcmpset_rel_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  drain_ring_lockless (struct ifmp_ring*,union ring_state,scalar_t__,int) ; 
 int /*<<< orphan*/  ifmp_ring_check_drainage (struct ifmp_ring*,int /*<<< orphan*/ ) ; 
 int increment_idx (struct ifmp_ring*,int,int) ; 
 int space_available (struct ifmp_ring*,union ring_state) ; 

int
ifmp_ring_enqueue(struct ifmp_ring *r, void **items, int n, int budget, int abdicate)
{
	union ring_state os, ns;
	uint16_t pidx_start, pidx_stop;
	int i;

	MPASS(items != NULL);
	MPASS(n > 0);

	/*
	 * Reserve room for the new items.  Our reservation, if successful, is
	 * from 'pidx_start' to 'pidx_stop'.
	 */
	os.state = r->state;
	for (;;) {
		if (n >= space_available(r, os)) {
			counter_u64_add(r->drops, n);
			MPASS(os.flags != IDLE);
			if (os.flags == STALLED)
				ifmp_ring_check_drainage(r, 0);
			return (ENOBUFS);
		}
		ns.state = os.state;
		ns.pidx_head = increment_idx(r, os.pidx_head, n);
		critical_enter();
		if (atomic_fcmpset_64(&r->state, &os.state, ns.state))
			break;
		critical_exit();
		cpu_spinwait();
	}
	pidx_start = os.pidx_head;
	pidx_stop = ns.pidx_head;

	/*
	 * Wait for other producers who got in ahead of us to enqueue their
	 * items, one producer at a time.  It is our turn when the ring's
	 * pidx_tail reaches the beginning of our reservation (pidx_start).
	 */
	while (ns.pidx_tail != pidx_start) {
		cpu_spinwait();
		ns.state = r->state;
	}

	/* Now it is our turn to fill up the area we reserved earlier. */
	i = pidx_start;
	do {
		r->items[i] = *items++;
		if (__predict_false(++i == r->size))
			i = 0;
	} while (i != pidx_stop);

	/*
	 * Update the ring's pidx_tail.  The release style atomic guarantees
	 * that the items are visible to any thread that sees the updated pidx.
	 */
	os.state = r->state;
	do {
		ns.state = os.state;
		ns.pidx_tail = pidx_stop;
		if (abdicate) {
			if (os.flags == IDLE)
				ns.flags = ABDICATED;
		} else
			ns.flags = BUSY;
	} while (atomic_fcmpset_rel_64(&r->state, &os.state, ns.state) == 0);
	critical_exit();
	counter_u64_add(r->enqueues, n);

	if (!abdicate) {
		/*
		 * Turn into a consumer if some other thread isn't active as a consumer
		 * already.
		 */
		if (os.flags != BUSY)
			drain_ring_lockless(r, ns, os.flags, budget);
	}

	return (0);
}