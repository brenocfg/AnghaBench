#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* timer_callback_func ) (int /*<<< orphan*/ ,void*) ;
typedef  size_t nfds_t ;
typedef  int /*<<< orphan*/  id_type ;
struct TYPE_7__ {size_t timers_count; TYPE_1__* timers; } ;
struct TYPE_6__ {scalar_t__ trigger_at; double interval; void* callback_data; int repeats; int /*<<< orphan*/  id; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_2__ EventLoopData ;

/* Variables and functions */
 scalar_t__ DBL_MAX ; 
 double monotonic () ; 
 int /*<<< orphan*/  removeTimer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  update_timers (TYPE_2__*) ; 

unsigned
dispatchTimers(EventLoopData *eld) {
    if (!eld->timers_count || eld->timers[0].trigger_at == DBL_MAX) return 0;
    static struct { timer_callback_func func; id_type id; void* data; bool repeats; } dispatches[sizeof(eld->timers)/sizeof(eld->timers[0])];
    unsigned num_dispatches = 0;
    double now = monotonic();
    for (nfds_t i = 0; i < eld->timers_count && eld->timers[i].trigger_at <= now; i++) {
        eld->timers[i].trigger_at = now + eld->timers[i].interval;
        dispatches[num_dispatches].func = eld->timers[i].callback;
        dispatches[num_dispatches].id = eld->timers[i].id;
        dispatches[num_dispatches].data = eld->timers[i].callback_data;
        dispatches[num_dispatches].repeats = eld->timers[i].repeats;
        num_dispatches++;
    }
    // we dispatch separately so that the callbacks can modify timers
    for (unsigned i = 0; i < num_dispatches; i++) {
        dispatches[i].func(dispatches[i].id, dispatches[i].data);
        if (!dispatches[i].repeats) {
            removeTimer(eld, dispatches[i].id);
        }
    }
    if (num_dispatches) update_timers(eld);
    return num_dispatches;
}