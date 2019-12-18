#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ _now_millisec; int /*<<< orphan*/  _timeouts; } ;
typedef  TYPE_1__ h2o_evloop_t ;

/* Variables and functions */
 scalar_t__ h2o_timerwheel_get_wake_at (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_now (TYPE_1__*) ; 

int32_t adjust_max_wait(h2o_evloop_t *loop, int32_t max_wait)
{
    uint64_t wake_at = h2o_timerwheel_get_wake_at(loop->_timeouts);

    update_now(loop);

    if (wake_at <= loop->_now_millisec) {
        max_wait = 0;
    } else {
        uint64_t delta = wake_at - loop->_now_millisec;
        if (delta < max_wait)
            max_wait = (int32_t)delta;
    }

    return max_wait;
}