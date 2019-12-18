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
typedef  int /*<<< orphan*/  dtrace_dynvar_t ;
struct TYPE_4__ {int /*<<< orphan*/  dtds_state; TYPE_2__* dtds_percpu; } ;
typedef  TYPE_1__ dtrace_dstate_t ;
struct TYPE_5__ {int /*<<< orphan*/ * dtdsc_rinsing; int /*<<< orphan*/ * dtdsc_clean; int /*<<< orphan*/ * dtdsc_dirty; } ;
typedef  TYPE_2__ dtrace_dstate_percpu_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_DSTATE_CLEAN ; 
 int NCPU ; 
 int /*<<< orphan*/ * dtrace_casptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_dynvar_failclean ; 
 int /*<<< orphan*/  dtrace_membar_producer () ; 
 int /*<<< orphan*/  dtrace_sync () ; 

void
dtrace_dynvar_clean(dtrace_dstate_t *dstate)
{
	dtrace_dynvar_t *dirty;
	dtrace_dstate_percpu_t *dcpu;
	dtrace_dynvar_t **rinsep;
	int i, j, work = 0;

	for (i = 0; i < NCPU; i++) {
		dcpu = &dstate->dtds_percpu[i];
		rinsep = &dcpu->dtdsc_rinsing;

		/*
		 * If the dirty list is NULL, there is no dirty work to do.
		 */
		if (dcpu->dtdsc_dirty == NULL)
			continue;

		if (dcpu->dtdsc_rinsing != NULL) {
			/*
			 * If the rinsing list is non-NULL, then it is because
			 * this CPU was selected to accept another CPU's
			 * dirty list -- and since that time, dirty buffers
			 * have accumulated.  This is a highly unlikely
			 * condition, but we choose to ignore the dirty
			 * buffers -- they'll be picked up a future cleanse.
			 */
			continue;
		}

		if (dcpu->dtdsc_clean != NULL) {
			/*
			 * If the clean list is non-NULL, then we're in a
			 * situation where a CPU has done deallocations (we
			 * have a non-NULL dirty list) but no allocations (we
			 * also have a non-NULL clean list).  We can't simply
			 * move the dirty list into the clean list on this
			 * CPU, yet we also don't want to allow this condition
			 * to persist, lest a short clean list prevent a
			 * massive dirty list from being cleaned (which in
			 * turn could lead to otherwise avoidable dynamic
			 * drops).  To deal with this, we look for some CPU
			 * with a NULL clean list, NULL dirty list, and NULL
			 * rinsing list -- and then we borrow this CPU to
			 * rinse our dirty list.
			 */
			for (j = 0; j < NCPU; j++) {
				dtrace_dstate_percpu_t *rinser;

				rinser = &dstate->dtds_percpu[j];

				if (rinser->dtdsc_rinsing != NULL)
					continue;

				if (rinser->dtdsc_dirty != NULL)
					continue;

				if (rinser->dtdsc_clean != NULL)
					continue;

				rinsep = &rinser->dtdsc_rinsing;
				break;
			}

			if (j == NCPU) {
				/*
				 * We were unable to find another CPU that
				 * could accept this dirty list -- we are
				 * therefore unable to clean it now.
				 */
				dtrace_dynvar_failclean++;
				continue;
			}
		}

		work = 1;

		/*
		 * Atomically move the dirty list aside.
		 */
		do {
			dirty = dcpu->dtdsc_dirty;

			/*
			 * Before we zap the dirty list, set the rinsing list.
			 * (This allows for a potential assertion in
			 * dtrace_dynvar():  if a free dynamic variable appears
			 * on a hash chain, either the dirty list or the
			 * rinsing list for some CPU must be non-NULL.)
			 */
			*rinsep = dirty;
			dtrace_membar_producer();
		} while (dtrace_casptr(&dcpu->dtdsc_dirty,
		    dirty, NULL) != dirty);
	}

	if (!work) {
		/*
		 * We have no work to do; we can simply return.
		 */
		return;
	}

	dtrace_sync();

	for (i = 0; i < NCPU; i++) {
		dcpu = &dstate->dtds_percpu[i];

		if (dcpu->dtdsc_rinsing == NULL)
			continue;

		/*
		 * We are now guaranteed that no hash chain contains a pointer
		 * into this dirty list; we can make it clean.
		 */
		ASSERT(dcpu->dtdsc_clean == NULL);
		dcpu->dtdsc_clean = dcpu->dtdsc_rinsing;
		dcpu->dtdsc_rinsing = NULL;
	}

	/*
	 * Before we actually set the state to be DTRACE_DSTATE_CLEAN, make
	 * sure that all CPUs have seen all of the dtdsc_clean pointers.
	 * This prevents a race whereby a CPU incorrectly decides that
	 * the state should be something other than DTRACE_DSTATE_CLEAN
	 * after dtrace_dynvar_clean() has completed.
	 */
	dtrace_sync();

	dstate->dtds_state = DTRACE_DSTATE_CLEAN;
}