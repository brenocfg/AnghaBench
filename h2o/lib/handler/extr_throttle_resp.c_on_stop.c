#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  timeout_entry; } ;
typedef  TYPE_1__ throttle_resp_t ;
typedef  int /*<<< orphan*/  h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_ostream_t ;

/* Variables and functions */
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_stop(h2o_ostream_t *_self, h2o_req_t *req)
{
    throttle_resp_t *self = (void *)_self;
    if (h2o_timer_is_linked(&self->timeout_entry))
        h2o_timer_unlink(&self->timeout_entry);
}