#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  head; int /*<<< orphan*/ * tail_ref; } ;
struct TYPE_8__ {int /*<<< orphan*/  _now_millisec; int /*<<< orphan*/  _timeouts; TYPE_1__ _statechanged; } ;
typedef  TYPE_2__ h2o_evloop_t ;

/* Variables and functions */
 TYPE_2__* h2o_mem_alloc (size_t) ; 
 int /*<<< orphan*/  h2o_timerwheel_create (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  update_now (TYPE_2__*) ; 

h2o_evloop_t *create_evloop(size_t sz)
{
    h2o_evloop_t *loop = h2o_mem_alloc(sz);

    memset(loop, 0, sz);
    loop->_statechanged.tail_ref = &loop->_statechanged.head;
    update_now(loop);
    /* 3 levels * 32-slots => 1 second goes into 2nd, becomes O(N) above approx. 31 seconds */
    loop->_timeouts = h2o_timerwheel_create(3, loop->_now_millisec);

    return loop;
}