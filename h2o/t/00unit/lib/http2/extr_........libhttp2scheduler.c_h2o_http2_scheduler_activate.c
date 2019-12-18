#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int _self_is_active; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ h2o_http2_scheduler_openref_t ;

/* Variables and functions */
 int /*<<< orphan*/  incr_active_cnt (int /*<<< orphan*/ *) ; 

void h2o_http2_scheduler_activate(h2o_http2_scheduler_openref_t *ref)
{
    if (ref->_self_is_active)
        return;
    ref->_self_is_active = 1;
    incr_active_cnt(&ref->node);
}