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
struct TYPE_2__ {int state; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SCTP_PROBE6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sctp_tcb*,int /*<<< orphan*/ *,struct sctp_tcb*,int /*<<< orphan*/ *,int) ; 
 int SCTP_STATE_ABOUT_TO_BE_FREED ; 
 int SCTP_STATE_MASK ; 
 int SCTP_STATE_SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  state__change ; 

void
sctp_add_substate(struct sctp_tcb *stcb, int substate)
{
#if defined(KDTRACE_HOOKS)
	int old_state = stcb->asoc.state;
#endif

	KASSERT((substate & SCTP_STATE_MASK) == 0,
	    ("sctp_add_substate: Can't set state (substate = %x)",
	    substate));
	stcb->asoc.state |= substate;
#if defined(KDTRACE_HOOKS)
	if (((substate & SCTP_STATE_ABOUT_TO_BE_FREED) &&
	    ((old_state & SCTP_STATE_ABOUT_TO_BE_FREED) == 0)) ||
	    ((substate & SCTP_STATE_SHUTDOWN_PENDING) &&
	    ((old_state & SCTP_STATE_SHUTDOWN_PENDING) == 0))) {
		SCTP_PROBE6(state__change, NULL, stcb, NULL, stcb, NULL, old_state);
	}
#endif
}