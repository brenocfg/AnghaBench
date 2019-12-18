#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ uint8_t ;
typedef  int u_int ;
struct TYPE_10__ {int oflags; scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PQ_ACTIVE ; 
 scalar_t__ PQ_COUNT ; 
 int VPO_UNMANAGED ; 
 int VPRC_WIRE_COUNT (int) ; 
 int /*<<< orphan*/  atomic_fcmpset_rel_int (int*,int*,int) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_mvqueue (TYPE_1__*,scalar_t__) ; 
 scalar_t__ vm_page_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unlock (TYPE_1__*) ; 
 scalar_t__ vm_page_unwire_noq (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_wire_sub (int) ; 

void
vm_page_unwire(vm_page_t m, uint8_t queue)
{
	u_int old;
	bool locked;

	KASSERT(queue < PQ_COUNT,
	    ("vm_page_unwire: invalid queue %u request for page %p", queue, m));

	if ((m->oflags & VPO_UNMANAGED) != 0) {
		if (vm_page_unwire_noq(m) && m->ref_count == 0)
			vm_page_free(m);
		return;
	}

	/*
	 * Update LRU state before releasing the wiring reference.
	 * We only need to do this once since we hold the page lock.
	 * Use a release store when updating the reference count to
	 * synchronize with vm_page_free_prep().
	 */
	old = m->ref_count;
	locked = false;
	do {
		KASSERT(VPRC_WIRE_COUNT(old) > 0,
		    ("vm_page_unwire: wire count underflow for page %p", m));
		if (!locked && VPRC_WIRE_COUNT(old) == 1) {
			vm_page_lock(m);
			locked = true;
			if (queue == PQ_ACTIVE && vm_page_queue(m) == PQ_ACTIVE)
				vm_page_reference(m);
			else
				vm_page_mvqueue(m, queue);
		}
	} while (!atomic_fcmpset_rel_int(&m->ref_count, &old, old - 1));

	/*
	 * Release the lock only after the wiring is released, to ensure that
	 * the page daemon does not encounter and dequeue the page while it is
	 * still wired.
	 */
	if (locked)
		vm_page_unlock(m);

	if (VPRC_WIRE_COUNT(old) == 1) {
		vm_wire_sub(1);
		if (old == 1)
			vm_page_free(m);
	}
}