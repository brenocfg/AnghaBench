#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ tcp_seq ;
struct tcpcb {int rcv_numsacks; scalar_t__ rcv_nxt; struct sackblk* sackblks; int /*<<< orphan*/  t_inpcb; } ;
struct sackblk {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (scalar_t__,char*) ; 
 int MAX_SACK_BLKS ; 
 scalar_t__ SEQ_GEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_GT (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bcopy (struct sackblk*,struct sackblk*,int) ; 

void
tcp_update_sack_list(struct tcpcb *tp, tcp_seq rcv_start, tcp_seq rcv_end)
{
	/*
	 * First reported block MUST be the most recent one.  Subsequent
	 * blocks SHOULD be in the order in which they arrived at the
	 * receiver.  These two conditions make the implementation fully
	 * compliant with RFC 2018.
	 */
	struct sackblk head_blk, saved_blks[MAX_SACK_BLKS];
	int num_head, num_saved, i;

	INP_WLOCK_ASSERT(tp->t_inpcb);

	/* Check arguments. */
	KASSERT(SEQ_LEQ(rcv_start, rcv_end), ("rcv_start <= rcv_end"));

	if ((rcv_start == rcv_end) &&
	    (tp->rcv_numsacks >= 1) &&
	    (rcv_end == tp->sackblks[0].end)) {
		/* retaining DSACK block below rcv_nxt (todrop) */
		head_blk = tp->sackblks[0];
	} else {
		/* SACK block for the received segment. */
		head_blk.start = rcv_start;
		head_blk.end = rcv_end;
	}

	/*
	 * Merge updated SACK blocks into head_blk, and save unchanged SACK
	 * blocks into saved_blks[].  num_saved will have the number of the
	 * saved SACK blocks.
	 */
	num_saved = 0;
	for (i = 0; i < tp->rcv_numsacks; i++) {
		tcp_seq start = tp->sackblks[i].start;
		tcp_seq end = tp->sackblks[i].end;
		if (SEQ_GEQ(start, end) || SEQ_LEQ(start, tp->rcv_nxt)) {
			/*
			 * Discard this SACK block.
			 */
		} else if (SEQ_LEQ(head_blk.start, end) &&
			   SEQ_GEQ(head_blk.end, start)) {
			/*
			 * Merge this SACK block into head_blk.  This SACK
			 * block itself will be discarded.
			 */
			/*
			 * |-|
			 *   |---|  merge
			 *
			 *     |-|
			 * |---|    merge
			 *
			 * |-----|
			 *   |-|    DSACK smaller
			 *
			 *   |-|
			 * |-----|  DSACK smaller
			 */
			if (head_blk.start == end)
				head_blk.start = start;
			else if (head_blk.end == start)
				head_blk.end = end;
			else {
				if (SEQ_LT(head_blk.start, start)) {
					tcp_seq temp = start;
					start = head_blk.start;
					head_blk.start = temp;
				}
				if (SEQ_GT(head_blk.end, end)) {
					tcp_seq temp = end;
					end = head_blk.end;
					head_blk.end = temp;
				}
				if ((head_blk.start != start) ||
				    (head_blk.end != end)) {
					if ((num_saved >= 1) &&
					   SEQ_GEQ(saved_blks[num_saved-1].start, start) &&
					   SEQ_LEQ(saved_blks[num_saved-1].end, end))
						num_saved--;
					saved_blks[num_saved].start = start;
					saved_blks[num_saved].end = end;
					num_saved++;
				}
			}
		} else {
			/*
			 * This block supercedes the prior block
			 */
			if ((num_saved >= 1) &&
			   SEQ_GEQ(saved_blks[num_saved-1].start, start) &&
			   SEQ_LEQ(saved_blks[num_saved-1].end, end))
				num_saved--;
			/*
			 * Save this SACK block.
			 */
			saved_blks[num_saved].start = start;
			saved_blks[num_saved].end = end;
			num_saved++;
		}
	}

	/*
	 * Update SACK list in tp->sackblks[].
	 */
	num_head = 0;
	if (SEQ_LT(rcv_start, rcv_end)) {
		/*
		 * The received data segment is an out-of-order segment.  Put
		 * head_blk at the top of SACK list.
		 */
		tp->sackblks[0] = head_blk;
		num_head = 1;
		/*
		 * If the number of saved SACK blocks exceeds its limit,
		 * discard the last SACK block.
		 */
		if (num_saved >= MAX_SACK_BLKS)
			num_saved--;
	}
	if ((rcv_start == rcv_end) &&
	    (rcv_start == tp->sackblks[0].end)) {
		num_head = 1;
	}
	if (num_saved > 0) {
		/*
		 * Copy the saved SACK blocks back.
		 */
		bcopy(saved_blks, &tp->sackblks[num_head],
		      sizeof(struct sackblk) * num_saved);
	}

	/* Save the number of SACK blocks. */
	tp->rcv_numsacks = num_head + num_saved;
}