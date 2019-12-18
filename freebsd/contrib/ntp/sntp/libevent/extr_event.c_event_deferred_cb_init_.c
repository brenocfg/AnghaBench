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
struct TYPE_2__ {int /*<<< orphan*/  evcb_selfcb; } ;
struct event_callback {int /*<<< orphan*/  evcb_closure; int /*<<< orphan*/  evcb_pri; void* evcb_arg; TYPE_1__ evcb_cb_union; } ;
typedef  int /*<<< orphan*/  ev_uint8_t ;
typedef  int /*<<< orphan*/  deferred_cb_fn ;

/* Variables and functions */
 int /*<<< orphan*/  EV_CLOSURE_CB_SELF ; 
 int /*<<< orphan*/  memset (struct event_callback*,int /*<<< orphan*/ ,int) ; 

void
event_deferred_cb_init_(struct event_callback *cb, ev_uint8_t priority, deferred_cb_fn fn, void *arg)
{
	memset(cb, 0, sizeof(*cb));
	cb->evcb_cb_union.evcb_selfcb = fn;
	cb->evcb_arg = arg;
	cb->evcb_pri = priority;
	cb->evcb_closure = EV_CLOSURE_CB_SELF;
}