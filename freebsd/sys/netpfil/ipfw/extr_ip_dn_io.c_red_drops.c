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
typedef  scalar_t__ uint32_t ;
typedef  size_t u_int ;
struct TYPE_4__ {scalar_t__ len_bytes; scalar_t__ length; } ;
struct dn_queue {int avg; int q_time; int count; int random; TYPE_1__ ni; struct dn_fsk* fs; } ;
struct TYPE_5__ {int flags; } ;
struct dn_fsk {size_t lookup_depth; int* w_q_lookup; scalar_t__ min_th; scalar_t__ max_th; void* c_4; void* c_2; int /*<<< orphan*/  max_pkt_size; TYPE_2__ fs; scalar_t__ c_1; scalar_t__ c_3; int /*<<< orphan*/  lookup_step; scalar_t__ w_q; } ;
typedef  int int64_t ;
struct TYPE_6__ {int curr_time; } ;

/* Variables and functions */
 int DN_IS_ECN ; 
 int DN_IS_GENTLE_RED ; 
 int DN_QSIZE_BYTES ; 
 int SCALE (int) ; 
 void* SCALE_MUL (int,int) ; 
 void* div64 (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ dn_cfg ; 
 int random () ; 

__attribute__((used)) static int
red_drops (struct dn_queue *q, int len)
{
	/*
	 * RED algorithm
	 *
	 * RED calculates the average queue size (avg) using a low-pass filter
	 * with an exponential weighted (w_q) moving average:
	 * 	avg  <-  (1-w_q) * avg + w_q * q_size
	 * where q_size is the queue length (measured in bytes or * packets).
	 *
	 * If q_size == 0, we compute the idle time for the link, and set
	 *	avg = (1 - w_q)^(idle/s)
	 * where s is the time needed for transmitting a medium-sized packet.
	 *
	 * Now, if avg < min_th the packet is enqueued.
	 * If avg > max_th the packet is dropped. Otherwise, the packet is
	 * dropped with probability P function of avg.
	 */

	struct dn_fsk *fs = q->fs;
	int64_t p_b = 0;

	/* Queue in bytes or packets? */
	uint32_t q_size = (fs->fs.flags & DN_QSIZE_BYTES) ?
	    q->ni.len_bytes : q->ni.length;

	/* Average queue size estimation. */
	if (q_size != 0) {
		/* Queue is not empty, avg <- avg + (q_size - avg) * w_q */
		int diff = SCALE(q_size) - q->avg;
		int64_t v = SCALE_MUL((int64_t)diff, (int64_t)fs->w_q);

		q->avg += (int)v;
	} else {
		/*
		 * Queue is empty, find for how long the queue has been
		 * empty and use a lookup table for computing
		 * (1 - * w_q)^(idle_time/s) where s is the time to send a
		 * (small) packet.
		 * XXX check wraps...
		 */
		if (q->avg) {
			u_int t = div64((dn_cfg.curr_time - q->q_time), fs->lookup_step);

			q->avg = (t < fs->lookup_depth) ?
			    SCALE_MUL(q->avg, fs->w_q_lookup[t]) : 0;
		}
	}

	/* Should i drop? */
	if (q->avg < fs->min_th) {
		q->count = -1;
		return (0);	/* accept packet */
	}
	if (q->avg >= fs->max_th) {	/* average queue >=  max threshold */
		if (fs->fs.flags & DN_IS_ECN)
			return (1);
		if (fs->fs.flags & DN_IS_GENTLE_RED) {
			/*
			 * According to Gentle-RED, if avg is greater than
			 * max_th the packet is dropped with a probability
			 *	 p_b = c_3 * avg - c_4
			 * where c_3 = (1 - max_p) / max_th
			 *       c_4 = 1 - 2 * max_p
			 */
			p_b = SCALE_MUL((int64_t)fs->c_3, (int64_t)q->avg) -
			    fs->c_4;
		} else {
			q->count = -1;
			return (1);
		}
	} else if (q->avg > fs->min_th) {
		if (fs->fs.flags & DN_IS_ECN)
			return (1);
		/*
		 * We compute p_b using the linear dropping function
		 *	 p_b = c_1 * avg - c_2
		 * where c_1 = max_p / (max_th - min_th)
		 * 	 c_2 = max_p * min_th / (max_th - min_th)
		 */
		p_b = SCALE_MUL((int64_t)fs->c_1, (int64_t)q->avg) - fs->c_2;
	}

	if (fs->fs.flags & DN_QSIZE_BYTES)
		p_b = div64((p_b * len) , fs->max_pkt_size);
	if (++q->count == 0)
		q->random = random() & 0xffff;
	else {
		/*
		 * q->count counts packets arrived since last drop, so a greater
		 * value of q->count means a greater packet drop probability.
		 */
		if (SCALE_MUL(p_b, SCALE((int64_t)q->count)) > q->random) {
			q->count = 0;
			/* After a drop we calculate a new random value. */
			q->random = random() & 0xffff;
			return (1);	/* drop */
		}
	}
	/* End of RED algorithm. */

	return (0);	/* accept */

}