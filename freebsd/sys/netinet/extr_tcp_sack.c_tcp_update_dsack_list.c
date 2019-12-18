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
typedef  scalar_t__ tcp_seq ;
struct tcpcb {scalar_t__ rcv_nxt; int rcv_numsacks; struct sackblk* sackblks; TYPE_2__* t_inpcb; } ;
struct sackblk {scalar_t__ end; scalar_t__ start; } ;
struct TYPE_4__ {TYPE_1__* inp_socket; } ;
struct TYPE_3__ {int so_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  KASSERT (scalar_t__,char*) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MAX_SACK_BLKS ; 
 scalar_t__ SEQ_GT (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LT (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_MIN (scalar_t__,scalar_t__) ; 
 int SO_DEBUG ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 

void
tcp_update_dsack_list(struct tcpcb *tp, tcp_seq rcv_start, tcp_seq rcv_end)
{
	struct sackblk head_blk,mid_blk,saved_blks[MAX_SACK_BLKS];
	int i, j, n, identical;
	tcp_seq start, end;

	INP_WLOCK_ASSERT(tp->t_inpcb);

	KASSERT(SEQ_LT(rcv_start, rcv_end), ("rcv_start < rcv_end"));

	if (tp->t_inpcb->inp_socket->so_options & SO_DEBUG) {
		log(LOG_DEBUG, "\nDSACK update: %d..%d, rcv_nxt: %u\n",
		rcv_start, rcv_end, tp->rcv_nxt);
	}

	if (SEQ_LT(rcv_end, tp->rcv_nxt) ||
	    ((rcv_end == tp->rcv_nxt) &&
	     (tp->rcv_numsacks > 0 ) &&
	     (tp->sackblks[0].end == tp->rcv_nxt))) {
		saved_blks[0].start = rcv_start;
		saved_blks[0].end = rcv_end;
	} else {
		saved_blks[0].start = saved_blks[0].end = 0;
	}

	head_blk.start = head_blk.end = 0;
	mid_blk.start = rcv_start;
	mid_blk.end = rcv_end;
	identical = 0;

	for (i = 0; i < tp->rcv_numsacks; i++) {
		start = tp->sackblks[i].start;
		end = tp->sackblks[i].end;
		if (SEQ_LT(rcv_end, start)) {
			/* pkt left to sack blk */
			continue;
		}
		if (SEQ_GT(rcv_start, end)) {
			/* pkt right to sack blk */
			continue;
		}
		if (SEQ_GT(tp->rcv_nxt, end)) {
			if ((SEQ_MAX(rcv_start, start) != SEQ_MIN(rcv_end, end)) &&
			    (SEQ_GT(head_blk.start, SEQ_MAX(rcv_start, start)) ||
			    (head_blk.start == head_blk.end))) {
				head_blk.start = SEQ_MAX(rcv_start, start);
				head_blk.end = SEQ_MIN(rcv_end, end);
			}
			continue;
		}
		if (((head_blk.start == head_blk.end) ||
		     SEQ_LT(start, head_blk.start)) &&
		     (SEQ_GT(end, rcv_start) &&
		      SEQ_LEQ(start, rcv_end))) {
			head_blk.start = start;
			head_blk.end = end;
		}
		mid_blk.start = SEQ_MIN(mid_blk.start, start);
		mid_blk.end = SEQ_MAX(mid_blk.end, end);
		if ((mid_blk.start == start) &&
		    (mid_blk.end == end))
			identical = 1;
	}
	if (SEQ_LT(head_blk.start, head_blk.end)) {
		/* store overlapping range */
		saved_blks[0].start = SEQ_MAX(rcv_start, head_blk.start);
		saved_blks[0].end   = SEQ_MIN(rcv_end, head_blk.end);
	}
	n = 1;
	/*
	 * Second, if not ACKed, store the SACK block that
	 * overlaps with the DSACK block unless it is identical
	 */
	if ((SEQ_LT(tp->rcv_nxt, mid_blk.end) &&
	    !((mid_blk.start == saved_blks[0].start) &&
	    (mid_blk.end == saved_blks[0].end))) ||
	    identical == 1) {
		saved_blks[n].start = mid_blk.start;
		saved_blks[n++].end = mid_blk.end;
	}
	for (j = 0; (j < tp->rcv_numsacks) && (n < MAX_SACK_BLKS); j++) {
		if (((SEQ_LT(tp->sackblks[j].end, mid_blk.start) ||
		      SEQ_GT(tp->sackblks[j].start, mid_blk.end)) &&
		    (SEQ_GT(tp->sackblks[j].start, tp->rcv_nxt))))
		saved_blks[n++] = tp->sackblks[j];
	}
	j = 0;
	for (i = 0; i < n; i++) {
		/* we can end up with a stale inital entry */
		if (SEQ_LT(saved_blks[i].start, saved_blks[i].end)) {
			tp->sackblks[j++] = saved_blks[i];
		}
	}
	tp->rcv_numsacks = j;
}