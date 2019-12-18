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
 int /*<<< orphan*/  SCTP_CLEAR_SUBSTATE (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_PROBE6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sctp_tcb*,int /*<<< orphan*/ *,struct sctp_tcb*,int /*<<< orphan*/ *,int) ; 
 int SCTP_STATE_EMPTY ; 
 int SCTP_STATE_INUSE ; 
 int SCTP_STATE_MASK ; 
 int SCTP_STATE_SHUTDOWN_ACK_SENT ; 
 int /*<<< orphan*/  SCTP_STATE_SHUTDOWN_PENDING ; 
 int SCTP_STATE_SHUTDOWN_RECEIVED ; 
 int SCTP_STATE_SHUTDOWN_SENT ; 
 int /*<<< orphan*/  state__change ; 

void
sctp_set_state(struct sctp_tcb *stcb, int new_state)
{
#if defined(KDTRACE_HOOKS)
	int old_state = stcb->asoc.state;
#endif

	KASSERT((new_state & ~SCTP_STATE_MASK) == 0,
	    ("sctp_set_state: Can't set substate (new_state = %x)",
	    new_state));
	stcb->asoc.state = (stcb->asoc.state & ~SCTP_STATE_MASK) | new_state;
	if ((new_state == SCTP_STATE_SHUTDOWN_RECEIVED) ||
	    (new_state == SCTP_STATE_SHUTDOWN_SENT) ||
	    (new_state == SCTP_STATE_SHUTDOWN_ACK_SENT)) {
		SCTP_CLEAR_SUBSTATE(stcb, SCTP_STATE_SHUTDOWN_PENDING);
	}
#if defined(KDTRACE_HOOKS)
	if (((old_state & SCTP_STATE_MASK) != new_state) &&
	    !(((old_state & SCTP_STATE_MASK) == SCTP_STATE_EMPTY) &&
	    (new_state == SCTP_STATE_INUSE))) {
		SCTP_PROBE6(state__change, NULL, stcb, NULL, stcb, NULL, old_state);
	}
#endif
}