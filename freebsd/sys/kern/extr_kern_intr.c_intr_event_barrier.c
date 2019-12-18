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
struct intr_event {int ie_phase; scalar_t__* ie_active; int /*<<< orphan*/  ie_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  atomic_store_rel_int (int*,int) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  atomic_thread_fence_seq_cst () ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intr_event_barrier(struct intr_event *ie)
{
	int phase;

	mtx_assert(&ie->ie_lock, MA_OWNED);
	phase = ie->ie_phase;

	/*
	 * Switch phase to direct future interrupts to the other active counter.
	 * Make sure that any preceding stores are visible before the switch.
	 */
	KASSERT(ie->ie_active[!phase] == 0, ("idle phase has activity"));
	atomic_store_rel_int(&ie->ie_phase, !phase);

	/*
	 * This code cooperates with wait-free iteration of ie_handlers
	 * in intr_event_handle.
	 * Make sure that the removal and the phase update are not reordered
	 * with the active count check.
	 * Note that no combination of acquire and release fences can provide
	 * that guarantee as Store->Load sequences can always be reordered.
	 */
	atomic_thread_fence_seq_cst();

	/*
	 * Now wait on the inactive phase.
	 * The acquire fence is needed so that that all post-barrier accesses
	 * are after the check.
	 */
	while (ie->ie_active[phase] > 0)
		cpu_spinwait();
	atomic_thread_fence_acq();
}