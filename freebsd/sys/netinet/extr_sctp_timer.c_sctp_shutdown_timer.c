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
struct TYPE_2__ {int /*<<< orphan*/  max_send_times; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_nets {int dummy; } ;
struct sctp_inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_TIMER_TYPE_SHUTDOWN ; 
 int /*<<< orphan*/  sctp_backoff_on_timeout (struct sctp_tcb*,struct sctp_nets*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_nets* sctp_find_alternate_net (struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_send_shutdown (struct sctp_tcb*,struct sctp_nets*) ; 
 scalar_t__ sctp_threshold_management (struct sctp_inpcb*,struct sctp_tcb*,struct sctp_nets*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,struct sctp_inpcb*,struct sctp_tcb*,struct sctp_nets*) ; 

int
sctp_shutdown_timer(struct sctp_inpcb *inp, struct sctp_tcb *stcb,
    struct sctp_nets *net)
{
	struct sctp_nets *alt;

	/* first threshold management */
	if (sctp_threshold_management(inp, stcb, net, stcb->asoc.max_send_times)) {
		/* Assoc is over */
		return (1);
	}
	sctp_backoff_on_timeout(stcb, net, 1, 0, 0);
	/* second select an alternative */
	alt = sctp_find_alternate_net(stcb, net, 0);

	/* third generate a shutdown into the queue for out net */
	sctp_send_shutdown(stcb, alt);

	/* fourth restart timer */
	sctp_timer_start(SCTP_TIMER_TYPE_SHUTDOWN, inp, stcb, alt);
	return (0);
}