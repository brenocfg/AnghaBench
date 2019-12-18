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
typedef  scalar_t__ tcp_seq ;
struct tcpopt {int to_flags; int to_nsacks; scalar_t__ to_sacks; } ;
struct TYPE_2__ {scalar_t__ sacked_bytes; scalar_t__ last_sack_ack; scalar_t__ sack_bytes_rexmit; } ;
struct tcpcb {scalar_t__ snd_una; scalar_t__ snd_max; scalar_t__ snd_fack; TYPE_1__ sackhint; int /*<<< orphan*/  snd_holes; int /*<<< orphan*/  t_inpcb; } ;
struct sackhole {scalar_t__ end; scalar_t__ start; scalar_t__ rxmit; } ;
struct sackblk {scalar_t__ start; scalar_t__ end; } ;
typedef  int /*<<< orphan*/  sack ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SEQ_GEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_GT (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ SEQ_LT (scalar_t__,scalar_t__) ; 
 void* SEQ_MAX (scalar_t__,scalar_t__) ; 
 void* SEQ_MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct sackhole* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sackhole* TAILQ_PREV (struct sackhole*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCPOLEN_SACK ; 
 int /*<<< orphan*/  TCP_MAX_SACK ; 
 int TOF_SACK ; 
 int /*<<< orphan*/  bcopy (scalar_t__,struct sackblk*,int) ; 
 void* ntohl (scalar_t__) ; 
 int /*<<< orphan*/  sackhole_head ; 
 int /*<<< orphan*/  scblink ; 
 struct sackhole* tcp_sackhole_insert (struct tcpcb*,scalar_t__,scalar_t__,struct sackhole*) ; 
 int /*<<< orphan*/  tcp_sackhole_remove (struct tcpcb*,struct sackhole*) ; 

int
tcp_sack_doack(struct tcpcb *tp, struct tcpopt *to, tcp_seq th_ack)
{
	struct sackhole *cur, *temp;
	struct sackblk sack, sack_blocks[TCP_MAX_SACK + 1], *sblkp;
	int i, j, num_sack_blks, sack_changed;

	INP_WLOCK_ASSERT(tp->t_inpcb);

	num_sack_blks = 0;
	sack_changed = 0;
	/*
	 * If SND.UNA will be advanced by SEG.ACK, and if SACK holes exist,
	 * treat [SND.UNA, SEG.ACK) as if it is a SACK block.
	 */
	if (SEQ_LT(tp->snd_una, th_ack) && !TAILQ_EMPTY(&tp->snd_holes)) {
		sack_blocks[num_sack_blks].start = tp->snd_una;
		sack_blocks[num_sack_blks++].end = th_ack;
	}
	/*
	 * Append received valid SACK blocks to sack_blocks[], but only if we
	 * received new blocks from the other side.
	 */
	if (to->to_flags & TOF_SACK) {
		tp->sackhint.sacked_bytes = 0;	/* reset */
		for (i = 0; i < to->to_nsacks; i++) {
			bcopy((to->to_sacks + i * TCPOLEN_SACK),
			    &sack, sizeof(sack));
			sack.start = ntohl(sack.start);
			sack.end = ntohl(sack.end);
			if (SEQ_GT(sack.end, sack.start) &&
			    SEQ_GT(sack.start, tp->snd_una) &&
			    SEQ_GT(sack.start, th_ack) &&
			    SEQ_LT(sack.start, tp->snd_max) &&
			    SEQ_GT(sack.end, tp->snd_una) &&
			    SEQ_LEQ(sack.end, tp->snd_max)) {
				sack_blocks[num_sack_blks++] = sack;
				tp->sackhint.sacked_bytes +=
				    (sack.end-sack.start);
			}
		}
	}
	/*
	 * Return if SND.UNA is not advanced and no valid SACK block is
	 * received.
	 */
	if (num_sack_blks == 0)
		return (sack_changed);

	/*
	 * Sort the SACK blocks so we can update the scoreboard with just one
	 * pass. The overhead of sorting up to 4+1 elements is less than
	 * making up to 4+1 passes over the scoreboard.
	 */
	for (i = 0; i < num_sack_blks; i++) {
		for (j = i + 1; j < num_sack_blks; j++) {
			if (SEQ_GT(sack_blocks[i].end, sack_blocks[j].end)) {
				sack = sack_blocks[i];
				sack_blocks[i] = sack_blocks[j];
				sack_blocks[j] = sack;
			}
		}
	}
	if (TAILQ_EMPTY(&tp->snd_holes))
		/*
		 * Empty scoreboard. Need to initialize snd_fack (it may be
		 * uninitialized or have a bogus value). Scoreboard holes
		 * (from the sack blocks received) are created later below
		 * (in the logic that adds holes to the tail of the
		 * scoreboard).
		 */
		tp->snd_fack = SEQ_MAX(tp->snd_una, th_ack);
	/*
	 * In the while-loop below, incoming SACK blocks (sack_blocks[]) and
	 * SACK holes (snd_holes) are traversed from their tails with just
	 * one pass in order to reduce the number of compares especially when
	 * the bandwidth-delay product is large.
	 *
	 * Note: Typically, in the first RTT of SACK recovery, the highest
	 * three or four SACK blocks with the same ack number are received.
	 * In the second RTT, if retransmitted data segments are not lost,
	 * the highest three or four SACK blocks with ack number advancing
	 * are received.
	 */
	sblkp = &sack_blocks[num_sack_blks - 1];	/* Last SACK block */
	tp->sackhint.last_sack_ack = sblkp->end;
	if (SEQ_LT(tp->snd_fack, sblkp->start)) {
		/*
		 * The highest SACK block is beyond fack.  Append new SACK
		 * hole at the tail.  If the second or later highest SACK
		 * blocks are also beyond the current fack, they will be
		 * inserted by way of hole splitting in the while-loop below.
		 */
		temp = tcp_sackhole_insert(tp, tp->snd_fack,sblkp->start,NULL);
		if (temp != NULL) {
			tp->snd_fack = sblkp->end;
			/* Go to the previous sack block. */
			sblkp--;
			sack_changed = 1;
		} else {
			/* 
			 * We failed to add a new hole based on the current 
			 * sack block.  Skip over all the sack blocks that 
			 * fall completely to the right of snd_fack and
			 * proceed to trim the scoreboard based on the
			 * remaining sack blocks.  This also trims the
			 * scoreboard for th_ack (which is sack_blocks[0]).
			 */
			while (sblkp >= sack_blocks && 
			       SEQ_LT(tp->snd_fack, sblkp->start))
				sblkp--;
			if (sblkp >= sack_blocks && 
			    SEQ_LT(tp->snd_fack, sblkp->end))
				tp->snd_fack = sblkp->end;
		}
	} else if (SEQ_LT(tp->snd_fack, sblkp->end)) {
		/* fack is advanced. */
		tp->snd_fack = sblkp->end;
		sack_changed = 1;
	}
	cur = TAILQ_LAST(&tp->snd_holes, sackhole_head); /* Last SACK hole. */
	/*
	 * Since the incoming sack blocks are sorted, we can process them
	 * making one sweep of the scoreboard.
	 */
	while (sblkp >= sack_blocks  && cur != NULL) {
		if (SEQ_GEQ(sblkp->start, cur->end)) {
			/*
			 * SACKs data beyond the current hole.  Go to the
			 * previous sack block.
			 */
			sblkp--;
			continue;
		}
		if (SEQ_LEQ(sblkp->end, cur->start)) {
			/*
			 * SACKs data before the current hole.  Go to the
			 * previous hole.
			 */
			cur = TAILQ_PREV(cur, sackhole_head, scblink);
			continue;
		}
		tp->sackhint.sack_bytes_rexmit -= (cur->rxmit - cur->start);
		KASSERT(tp->sackhint.sack_bytes_rexmit >= 0,
		    ("sackhint bytes rtx >= 0"));
		sack_changed = 1;
		if (SEQ_LEQ(sblkp->start, cur->start)) {
			/* Data acks at least the beginning of hole. */
			if (SEQ_GEQ(sblkp->end, cur->end)) {
				/* Acks entire hole, so delete hole. */
				temp = cur;
				cur = TAILQ_PREV(cur, sackhole_head, scblink);
				tcp_sackhole_remove(tp, temp);
				/*
				 * The sack block may ack all or part of the
				 * next hole too, so continue onto the next
				 * hole.
				 */
				continue;
			} else {
				/* Move start of hole forward. */
				cur->start = sblkp->end;
				cur->rxmit = SEQ_MAX(cur->rxmit, cur->start);
			}
		} else {
			/* Data acks at least the end of hole. */
			if (SEQ_GEQ(sblkp->end, cur->end)) {
				/* Move end of hole backward. */
				cur->end = sblkp->start;
				cur->rxmit = SEQ_MIN(cur->rxmit, cur->end);
			} else {
				/*
				 * ACKs some data in middle of a hole; need
				 * to split current hole
				 */
				temp = tcp_sackhole_insert(tp, sblkp->end,
				    cur->end, cur);
				if (temp != NULL) {
					if (SEQ_GT(cur->rxmit, temp->rxmit)) {
						temp->rxmit = cur->rxmit;
						tp->sackhint.sack_bytes_rexmit
						    += (temp->rxmit
						    - temp->start);
					}
					cur->end = sblkp->start;
					cur->rxmit = SEQ_MIN(cur->rxmit,
					    cur->end);
				}
			}
		}
		tp->sackhint.sack_bytes_rexmit += (cur->rxmit - cur->start);
		/*
		 * Testing sblkp->start against cur->start tells us whether
		 * we're done with the sack block or the sack hole.
		 * Accordingly, we advance one or the other.
		 */
		if (SEQ_LEQ(sblkp->start, cur->start))
			cur = TAILQ_PREV(cur, sackhole_head, scblink);
		else
			sblkp--;
	}
	return (sack_changed);
}