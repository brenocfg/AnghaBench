#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct event_callback {int /*<<< orphan*/  evcb_pri; } ;
typedef  int /*<<< orphan*/  ev_uint8_t ;

/* Variables and functions */

void
event_deferred_cb_set_priority_(struct event_callback *cb, ev_uint8_t priority)
{
	cb->evcb_pri = priority;
}