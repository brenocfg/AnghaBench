#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* evcb_cbfinalize ) (struct event_callback*,int /*<<< orphan*/ ) ;} ;
struct event_callback {int evcb_flags; int evcb_closure; int /*<<< orphan*/  evcb_arg; TYPE_3__ evcb_cb_union; } ;
struct event_base {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* evcb_evfinalize ) (struct event*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ evcb_cb_union; } ;
struct event {int ev_flags; int /*<<< orphan*/  ev_arg; TYPE_2__ ev_evcallback; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENT_DEL_EVEN_IF_FINALIZING ; 
 int EVLIST_FINALIZING ; 
 int EVLIST_INIT ; 
 int EVLIST_INTERNAL ; 
#define  EV_CLOSURE_CB_FINALIZE 130 
#define  EV_CLOSURE_EVENT_FINALIZE 129 
#define  EV_CLOSURE_EVENT_FINALIZE_FREE 128 
 int /*<<< orphan*/  event_callback_cancel_nolock_ (struct event_base*,struct event_callback*,int) ; 
 struct event* event_callback_to_event (struct event_callback*) ; 
 int /*<<< orphan*/  event_del_ (struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct event*) ; 
 int /*<<< orphan*/  stub1 (struct event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct event_callback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  th_base_lock ; 

__attribute__((used)) static int
event_base_cancel_single_callback_(struct event_base *base,
    struct event_callback *evcb,
    int run_finalizers)
{
	int result = 0;

	if (evcb->evcb_flags & EVLIST_INIT) {
		struct event *ev = event_callback_to_event(evcb);
		if (!(ev->ev_flags & EVLIST_INTERNAL)) {
			event_del_(ev, EVENT_DEL_EVEN_IF_FINALIZING);
			result = 1;
		}
	} else {
		EVBASE_ACQUIRE_LOCK(base, th_base_lock);
		event_callback_cancel_nolock_(base, evcb, 1);
		EVBASE_RELEASE_LOCK(base, th_base_lock);
		result = 1;
	}

	if (run_finalizers && (evcb->evcb_flags & EVLIST_FINALIZING)) {
		switch (evcb->evcb_closure) {
		case EV_CLOSURE_EVENT_FINALIZE:
		case EV_CLOSURE_EVENT_FINALIZE_FREE: {
			struct event *ev = event_callback_to_event(evcb);
			ev->ev_evcallback.evcb_cb_union.evcb_evfinalize(ev, ev->ev_arg);
			if (evcb->evcb_closure == EV_CLOSURE_EVENT_FINALIZE_FREE)
				mm_free(ev);
			break;
		}
		case EV_CLOSURE_CB_FINALIZE:
			evcb->evcb_cb_union.evcb_cbfinalize(evcb, evcb->evcb_arg);
			break;
		default:
			break;
		}
	}
	return result;
}