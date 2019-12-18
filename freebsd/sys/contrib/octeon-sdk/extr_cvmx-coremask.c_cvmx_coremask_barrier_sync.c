#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* s; } ;
struct TYPE_3__ {unsigned int coremask; int exit; unsigned int checkin; } ;

/* Variables and functions */
 int CVMX_COREMASK_MAX_SYNCS ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int cvmx_coremask_core (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ state ; 

void cvmx_coremask_barrier_sync(unsigned int coremask)
{
    int i;
    unsigned int target;

    assert(coremask != 0);

    cvmx_spinlock_lock(&state.lock);

    for (i = 0; i < CVMX_COREMASK_MAX_SYNCS; i++) {

        if (state.s[i].coremask == 0) {
            /* end of existing coremask list, create new entry, fall-thru */
            state.s[i].coremask = coremask;
        }

        if (state.s[i].coremask == coremask) {

            target = state.s[i].exit + 1;  /* wrap-around at 32b */

            state.s[i].checkin |= cvmx_coremask_core(cvmx_get_core_num());
            if (state.s[i].checkin == coremask) {
                state.s[i].checkin = 0;
                state.s[i].exit = target;  /* signal exit condition */
            }
            cvmx_spinlock_unlock(&state.lock);

            while (state.s[i].exit != target)
                ;

            return;
        }
    }

    /* error condition - coremask array overflowed */
    cvmx_spinlock_unlock(&state.lock);
    assert(0);
}