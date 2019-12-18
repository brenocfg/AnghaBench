#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct event_base {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  evcb_evfinalize; } ;
struct TYPE_4__ {TYPE_1__ evcb_cb_union; } ;
struct event {int /*<<< orphan*/  ev_flags; TYPE_2__ ev_evcallback; int /*<<< orphan*/  ev_closure; } ;
typedef  int /*<<< orphan*/  event_finalize_callback_fn ;
typedef  int /*<<< orphan*/  ev_uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DEL_NOBLOCK ; 
 unsigned int EVENT_FINALIZE_FREE_ ; 
 int /*<<< orphan*/  EVLIST_FINALIZING ; 
 int /*<<< orphan*/  EV_CLOSURE_EVENT_FINALIZE ; 
 int /*<<< orphan*/  EV_CLOSURE_EVENT_FINALIZE_FREE ; 
 int /*<<< orphan*/  EV_FINALIZE ; 
 int /*<<< orphan*/  event_active_nolock_ (struct event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_del_nolock_ (struct event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
event_finalize_nolock_(struct event_base *base, unsigned flags, struct event *ev, event_finalize_callback_fn cb)
{
	ev_uint8_t closure = (flags & EVENT_FINALIZE_FREE_) ?
	    EV_CLOSURE_EVENT_FINALIZE_FREE : EV_CLOSURE_EVENT_FINALIZE;

	event_del_nolock_(ev, EVENT_DEL_NOBLOCK);
	ev->ev_closure = closure;
	ev->ev_evcallback.evcb_cb_union.evcb_evfinalize = cb;
	event_active_nolock_(ev, EV_FINALIZE, 1);
	ev->ev_flags |= EVLIST_FINALIZING;
	return 0;
}