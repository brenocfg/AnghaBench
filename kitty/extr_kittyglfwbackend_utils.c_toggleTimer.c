#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t nfds_t ;
typedef  scalar_t__ id_type ;
struct TYPE_6__ {size_t timers_count; TYPE_1__* timers; } ;
struct TYPE_5__ {scalar_t__ id; double interval; double trigger_at; } ;
typedef  TYPE_2__ EventLoopData ;

/* Variables and functions */
 double DBL_MAX ; 
 double monotonic () ; 
 int /*<<< orphan*/  update_timers (TYPE_2__*) ; 

void
toggleTimer(EventLoopData *eld, id_type timer_id, int enabled) {
    for (nfds_t i = 0; i < eld->timers_count; i++) {
        if (eld->timers[i].id == timer_id) {
            double trigger_at = enabled ? (monotonic() + eld->timers[i].interval) : DBL_MAX;
            if (trigger_at != eld->timers[i].trigger_at) {
                eld->timers[i].trigger_at = trigger_at;
                update_timers(eld);
            }
            break;
        }
    }
}