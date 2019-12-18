#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int known_cores; unsigned int core_finished; unsigned int focus_core; scalar_t__ ever_been_in_debug; } ;
typedef  TYPE_1__ cvmx_debug_state_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int CVMX_MAX_CORES ; 
 int cvmx_debug_core_mask () ; 
 TYPE_1__ cvmx_debug_get_state () ; 
 TYPE_4__* cvmx_debug_globals ; 
 int /*<<< orphan*/  cvmx_debug_printf (char*,...) ; 
 int /*<<< orphan*/  cvmx_debug_putcorepacket (char*,unsigned int) ; 
 int /*<<< orphan*/  cvmx_debug_putpacket_noformat (char*) ; 
 int /*<<< orphan*/  cvmx_debug_set_focus_core (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  cvmx_debug_trigger_exception () ; 
 int /*<<< orphan*/  cvmx_debug_update_state (TYPE_1__) ; 
 unsigned int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void cvmx_debug_finish(void)
{
    unsigned coreid = cvmx_get_core_num();
    cvmx_debug_state_t state;

    if (!cvmx_debug_globals) return;
    cvmx_debug_printf ("Debug _exit reached!, core %d, cvmx_debug_globals = %p\n", coreid, cvmx_debug_globals);

#ifndef CVMX_BUILD_FOR_LINUX_KERNEL
    fflush (stdout);
    fflush (stderr);
#endif

    cvmx_spinlock_lock(&cvmx_debug_globals->lock);
    state = cvmx_debug_get_state();
    state.known_cores ^= (1u << coreid);
    state.core_finished |= (1u <<coreid);
    cvmx_debug_update_state(state);

    /* Tell the user the core has finished. */
    if (state.ever_been_in_debug)
        cvmx_debug_putcorepacket("finished.", coreid);

    /* Notify the debugger if all cores have completed the program */
    if ((cvmx_debug_core_mask () & state.core_finished) == cvmx_debug_core_mask ())
    {
        cvmx_debug_printf("All cores done!\n");
        if (state.ever_been_in_debug)
            cvmx_debug_putpacket_noformat("D0");
    }
    if (state.focus_core == coreid && state.known_cores != 0)
    {
        /* Loop through cores looking for someone to handle interrupts.
           Since we already check that known_cores is non zero, this
           should always find a core */
        unsigned newcore;
        for (newcore = 0; newcore < CVMX_MAX_CORES; newcore++)
        {
           if (state.known_cores & (1u<<newcore))
           {
               cvmx_debug_printf("Routing uart interrupts to Core #%u.\n", newcore);
               cvmx_debug_set_focus_core(&state, newcore);
               cvmx_debug_update_state(state);
               break;
            }
        }
    }
    cvmx_spinlock_unlock(&cvmx_debug_globals->lock);

    /* If we ever been in the debug, report to it that we have exited the core. */
    if (state.ever_been_in_debug)
        cvmx_debug_trigger_exception();
}