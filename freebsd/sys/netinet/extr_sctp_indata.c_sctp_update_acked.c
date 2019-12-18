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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ total_flight; scalar_t__ peers_rwnd; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_shutdown_chunk {int /*<<< orphan*/  cumulative_tsn_ack; } ;

/* Variables and functions */
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_express_handle_sack (struct sctp_tcb*,scalar_t__,scalar_t__,int*,int /*<<< orphan*/ ) ; 

void
sctp_update_acked(struct sctp_tcb *stcb, struct sctp_shutdown_chunk *cp, int *abort_flag)
{
	/* Copy cum-ack */
	uint32_t cum_ack, a_rwnd;

	cum_ack = ntohl(cp->cumulative_tsn_ack);
	/* Arrange so a_rwnd does NOT change */
	a_rwnd = stcb->asoc.peers_rwnd + stcb->asoc.total_flight;

	/* Now call the express sack handling */
	sctp_express_handle_sack(stcb, cum_ack, a_rwnd, abort_flag, 0);
}