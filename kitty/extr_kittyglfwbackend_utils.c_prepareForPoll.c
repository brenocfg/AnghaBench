#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t nfds_t ;
struct TYPE_7__ {size_t watches_count; TYPE_1__* timers; int /*<<< orphan*/  timers_count; TYPE_2__* fds; } ;
struct TYPE_6__ {scalar_t__ revents; } ;
struct TYPE_5__ {double trigger_at; } ;
typedef  TYPE_3__ EventLoopData ;

/* Variables and functions */
 double DBL_MAX ; 
 double monotonic () ; 

double
prepareForPoll(EventLoopData *eld, double timeout) {
    for (nfds_t i = 0; i < eld->watches_count; i++) eld->fds[i].revents = 0;
    if (!eld->timers_count || eld->timers[0].trigger_at == DBL_MAX) return timeout;
    double now = monotonic(), next_repeat_at = eld->timers[0].trigger_at;
    if (timeout < 0 || now + timeout > next_repeat_at) {
        timeout = next_repeat_at <= now ? 0 : next_repeat_at - now;
    }
    return timeout;
}