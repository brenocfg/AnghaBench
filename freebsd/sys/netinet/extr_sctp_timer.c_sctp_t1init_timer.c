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
struct TYPE_2__ {scalar_t__ initial_init_rto_max; int numnets; struct sctp_nets* primary_destination; scalar_t__ dropped_special_cnt; int /*<<< orphan*/  max_init_times; scalar_t__ delayed_connection; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_nets {scalar_t__ RTO; } ;
struct sctp_inpcb {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 scalar_t__ SCTP_STATE_COOKIE_WAIT ; 
 int /*<<< orphan*/  sctp_backoff_on_timeout (struct sctp_tcb*,struct sctp_nets*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_nets* sctp_find_alternate_net (struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_move_chunks_from_net (struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_send_initiate (struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_threshold_management (struct sctp_inpcb*,struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ) ; 

int
sctp_t1init_timer(struct sctp_inpcb *inp,
    struct sctp_tcb *stcb,
    struct sctp_nets *net)
{
	/* bump the thresholds */
	if (stcb->asoc.delayed_connection) {
		/*
		 * special hook for delayed connection. The library did NOT
		 * complete the rest of its sends.
		 */
		stcb->asoc.delayed_connection = 0;
		sctp_send_initiate(inp, stcb, SCTP_SO_NOT_LOCKED);
		return (0);
	}
	if (SCTP_GET_STATE(stcb) != SCTP_STATE_COOKIE_WAIT) {
		return (0);
	}
	if (sctp_threshold_management(inp, stcb, net,
	    stcb->asoc.max_init_times)) {
		/* Association was destroyed */
		return (1);
	}
	stcb->asoc.dropped_special_cnt = 0;
	sctp_backoff_on_timeout(stcb, stcb->asoc.primary_destination, 1, 0, 0);
	if (stcb->asoc.initial_init_rto_max < net->RTO) {
		net->RTO = stcb->asoc.initial_init_rto_max;
	}
	if (stcb->asoc.numnets > 1) {
		/* If we have more than one addr use it */
		struct sctp_nets *alt;

		alt = sctp_find_alternate_net(stcb, stcb->asoc.primary_destination, 0);
		if (alt != stcb->asoc.primary_destination) {
			sctp_move_chunks_from_net(stcb, stcb->asoc.primary_destination);
			stcb->asoc.primary_destination = alt;
		}
	}
	/* Send out a new init */
	sctp_send_initiate(inp, stcb, SCTP_SO_NOT_LOCKED);
	return (0);
}