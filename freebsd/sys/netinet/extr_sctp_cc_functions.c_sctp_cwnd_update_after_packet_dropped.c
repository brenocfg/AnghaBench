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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {unsigned int max_burst; int /*<<< orphan*/  my_vtag; scalar_t__ seen_a_sack_this_pkt; } ;
struct sctp_tcb {int rport; TYPE_1__* sctp_ep; TYPE_2__ asoc; } ;
struct sctp_pktdrop_chunk {int /*<<< orphan*/  current_onq; int /*<<< orphan*/  bottle_bw; } ;
struct sctp_nets {int cwnd; scalar_t__ flight_size; int rtt; int prev_cwnd; int mtu; int ssthresh; scalar_t__ partial_bytes_acked; } ;
struct TYPE_3__ {int sctp_lport; } ;

/* Variables and functions */
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CWND_LOG_FROM_SAT ; 
 int SCTP_CWND_MONITOR_ENABLE ; 
 int /*<<< orphan*/  SDT_PROBE5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_nets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sctp_nets*,int,scalar_t__) ; 
 int /*<<< orphan*/  cwnd ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pd ; 
 int /*<<< orphan*/  sctp ; 
 int /*<<< orphan*/  sctp_enforce_cwnd_limit (TYPE_2__*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_log_cwnd (struct sctp_tcb*,struct sctp_nets*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_logging_level ; 

__attribute__((used)) static void
sctp_cwnd_update_after_packet_dropped(struct sctp_tcb *stcb,
    struct sctp_nets *net, struct sctp_pktdrop_chunk *cp,
    uint32_t *bottle_bw, uint32_t *on_queue)
{
	uint32_t bw_avail;
	unsigned int incr;
	int old_cwnd = net->cwnd;

	/* get bottle neck bw */
	*bottle_bw = ntohl(cp->bottle_bw);
	/* and whats on queue */
	*on_queue = ntohl(cp->current_onq);
	/*
	 * adjust the on-queue if our flight is more it could be that the
	 * router has not yet gotten data "in-flight" to it
	 */
	if (*on_queue < net->flight_size) {
		*on_queue = net->flight_size;
	}
	/* rtt is measured in micro seconds, bottle_bw in bytes per second */
	bw_avail = (uint32_t)(((uint64_t)(*bottle_bw) * net->rtt) / (uint64_t)1000000);
	if (bw_avail > *bottle_bw) {
		/*
		 * Cap the growth to no more than the bottle neck. This can
		 * happen as RTT slides up due to queues. It also means if
		 * you have more than a 1 second RTT with a empty queue you
		 * will be limited to the bottle_bw per second no matter if
		 * other points have 1/2 the RTT and you could get more
		 * out...
		 */
		bw_avail = *bottle_bw;
	}
	if (*on_queue > bw_avail) {
		/*
		 * No room for anything else don't allow anything else to be
		 * "added to the fire".
		 */
		int seg_inflight, seg_onqueue, my_portion;

		net->partial_bytes_acked = 0;
		/* how much are we over queue size? */
		incr = *on_queue - bw_avail;
		if (stcb->asoc.seen_a_sack_this_pkt) {
			/*
			 * undo any cwnd adjustment that the sack might have
			 * made
			 */
			net->cwnd = net->prev_cwnd;
		}
		/* Now how much of that is mine? */
		seg_inflight = net->flight_size / net->mtu;
		seg_onqueue = *on_queue / net->mtu;
		my_portion = (incr * seg_inflight) / seg_onqueue;

		/* Have I made an adjustment already */
		if (net->cwnd > net->flight_size) {
			/*
			 * for this flight I made an adjustment we need to
			 * decrease the portion by a share our previous
			 * adjustment.
			 */
			int diff_adj;

			diff_adj = net->cwnd - net->flight_size;
			if (diff_adj > my_portion)
				my_portion = 0;
			else
				my_portion -= diff_adj;
		}
		/*
		 * back down to the previous cwnd (assume we have had a sack
		 * before this packet). minus what ever portion of the
		 * overage is my fault.
		 */
		net->cwnd -= my_portion;

		/* we will NOT back down more than 1 MTU */
		if (net->cwnd <= net->mtu) {
			net->cwnd = net->mtu;
		}
		/* force into CA */
		net->ssthresh = net->cwnd - 1;
	} else {
		/*
		 * Take 1/4 of the space left or max burst up .. whichever
		 * is less.
		 */
		incr = (bw_avail - *on_queue) >> 2;
		if ((stcb->asoc.max_burst > 0) &&
		    (stcb->asoc.max_burst * net->mtu < incr)) {
			incr = stcb->asoc.max_burst * net->mtu;
		}
		net->cwnd += incr;
	}
	if (net->cwnd > bw_avail) {
		/* We can't exceed the pipe size */
		net->cwnd = bw_avail;
	}
	if (net->cwnd < net->mtu) {
		/* We always have 1 MTU */
		net->cwnd = net->mtu;
	}
	sctp_enforce_cwnd_limit(&stcb->asoc, net);
	if (net->cwnd - old_cwnd != 0) {
		/* log only changes */
		SDT_PROBE5(sctp, cwnd, net, pd,
		    stcb->asoc.my_vtag,
		    ((stcb->sctp_ep->sctp_lport << 16) | (stcb->rport)),
		    net,
		    old_cwnd, net->cwnd);
		if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_CWND_MONITOR_ENABLE) {
			sctp_log_cwnd(stcb, net, (net->cwnd - old_cwnd),
			    SCTP_CWND_LOG_FROM_SAT);
		}
	}
}