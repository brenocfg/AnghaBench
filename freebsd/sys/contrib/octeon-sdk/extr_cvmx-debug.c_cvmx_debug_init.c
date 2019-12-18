#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cvmx_spinlock_t ;
struct TYPE_7__ {unsigned int known_cores; unsigned int core_finished; int focus_core; unsigned int active_cores; int focus_switch; int step_isr; } ;
typedef  TYPE_1__ cvmx_debug_state_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* install_break_handler ) () ;int /*<<< orphan*/  (* init ) () ;} ;
typedef  TYPE_2__ cvmx_debug_comm_t ;
struct TYPE_9__ {size_t comm_type; int init_complete; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CVMX_MAX_CORES ; 
 int /*<<< orphan*/  CVMX_SYNCW ; 
 int /*<<< orphan*/ ** __cvmx_debug_stack_top_all ; 
 int /*<<< orphan*/  cvmx_coremask_barrier_sync (unsigned int) ; 
 scalar_t__ cvmx_coremask_first_core (unsigned int) ; 
 scalar_t__ cvmx_debug_booted () ; 
 TYPE_2__** cvmx_debug_comms ; 
 unsigned int cvmx_debug_core_mask () ; 
 int /*<<< orphan*/  cvmx_debug_enabled () ; 
 TYPE_1__ cvmx_debug_get_state () ; 
 TYPE_4__* cvmx_debug_globals ; 
 int /*<<< orphan*/  cvmx_debug_globals_check_version () ; 
 int /*<<< orphan*/  cvmx_debug_init_globals () ; 
 int /*<<< orphan*/  cvmx_debug_install_handler (int) ; 
 int /*<<< orphan*/  cvmx_debug_printf (char*,int) ; 
 int /*<<< orphan*/ ** cvmx_debug_stack_all ; 
 int /*<<< orphan*/  cvmx_debug_trigger_exception () ; 
 int /*<<< orphan*/  cvmx_debug_update_state (TYPE_1__) ; 
 int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

void cvmx_debug_init(void)
{
    cvmx_debug_state_t state;
    int core;
    const cvmx_debug_comm_t *comm;
    cvmx_spinlock_t *lock;
    unsigned int coremask = cvmx_debug_core_mask();

    if (!cvmx_debug_enabled())
        return;

    cvmx_debug_init_globals();

#ifndef CVMX_BUILD_FOR_LINUX_KERNEL
    // Put a barrier until all cores have got to this point.
    cvmx_coremask_barrier_sync(coremask);
#endif
    cvmx_debug_globals_check_version();


    comm = cvmx_debug_comms[cvmx_debug_globals->comm_type];
    lock = &cvmx_debug_globals->lock;

    core = cvmx_get_core_num();
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
    /*  Install the debugger handler on the cores. */
    {
        int core1 = 0;
        for (core1 = 0; core1 < CVMX_MAX_CORES; core1++)
        {
            if ((1u<<core1) & coremask)
                cvmx_debug_install_handler(core1);
        }
    }
#else
    cvmx_debug_install_handler(core);
#endif

    if (comm->init)
        comm->init();

    {
        cvmx_spinlock_lock(lock);
        state = cvmx_debug_get_state();
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
        state.known_cores |= coremask;
        state.core_finished &= ~coremask;
#else
        state.known_cores |= (1u << core);
        state.core_finished &= ~(1u << core);
#endif
        cvmx_debug_update_state(state);
        cvmx_spinlock_unlock(lock);
    }

#ifndef CVMX_BUILD_FOR_LINUX_KERNEL
    // Put a barrier until all cores have got to this point.
    cvmx_coremask_barrier_sync(coremask);

    if (cvmx_coremask_first_core(coremask))
#endif
    {
        cvmx_debug_printf("cvmx_debug_init core: %d\n", core);
        state = cvmx_debug_get_state();
        state.focus_core = core;
        state.active_cores = state.known_cores;
        state.focus_switch = 1;
        state.step_isr = 1;
        cvmx_debug_printf("Known cores at init: 0x%x\n", (int)state.known_cores);
        cvmx_debug_update_state(state);

        /* Initialize __cvmx_debug_stack_top_all. */
#ifdef CVMX_BUILD_FOR_LINUX_KERNEL
        {
            int i;
            for (i = 0; i < CVMX_MAX_CORES; i++)
                __cvmx_debug_stack_top_all[i] = &cvmx_debug_stack_all[i][8*1024];
        }
#endif
        cvmx_debug_globals->init_complete = 1;
        CVMX_SYNCW;
    }
    while (!cvmx_debug_globals->init_complete)
    {
        /* Spin waiting for init to complete */
    }

    if (cvmx_debug_booted())
        cvmx_debug_trigger_exception();

    /*  Install the break handler after might tripper the debugger exception. */
#ifndef CVMX_BUILD_FOR_LINUX_KERNEL
    if (cvmx_coremask_first_core(coremask))
#endif
    {
        if (comm->install_break_handler)
            comm->install_break_handler();
    }
}