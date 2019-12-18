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
struct TYPE_6__ {scalar_t__ len; } ;
struct mbuf {TYPE_3__ m_pkthdr; } ;
struct TYPE_5__ {int opt; } ;
struct TYPE_4__ {int /*<<< orphan*/  yellow_pkts; int /*<<< orphan*/  droped_pkts; int /*<<< orphan*/  red_pkts; } ;
struct hookinfo {size_t q_last; int q_first; int te; int tc; int /*<<< orphan*/  q_mtx; TYPE_2__ conf; struct mbuf** q; TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  item_p ;

/* Variables and functions */
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int NG_CAR_COUNT_PACKETS ; 
 int NG_CAR_QUEUE_MIN_TH ; 
 int NG_CAR_QUEUE_SIZE ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_car_schedule (struct hookinfo*) ; 

__attribute__((used)) static void
ng_car_enqueue(struct hookinfo *hinfo, item_p item)
{
	struct mbuf 	*m;
	int		len;

	NGI_GET_M(item, m);
	NG_FREE_ITEM(item);

	/* Lock queue mutex. */
	mtx_lock(&hinfo->q_mtx);

	/* Calculate used queue length. */
	len = hinfo->q_last - hinfo->q_first;
	if (len < 0)
		len += NG_CAR_QUEUE_SIZE;

	/* If queue is overflowed or we have no RED tokens. */
	if ((len >= (NG_CAR_QUEUE_SIZE - 1)) ||
	    (hinfo->te + len >= NG_CAR_QUEUE_SIZE)) {
		/* Drop packet. */
		++hinfo->stats.red_pkts;
		++hinfo->stats.droped_pkts;
		NG_FREE_M(m);

		hinfo->te = 0;
	} else {
		/* This packet is yellow. */
		++hinfo->stats.yellow_pkts;

		/* Enqueue packet. */
		hinfo->q[hinfo->q_last] = m;
		hinfo->q_last++;
		if (hinfo->q_last >= NG_CAR_QUEUE_SIZE)
			hinfo->q_last = 0;

		/* Use RED tokens. */
		if (len > NG_CAR_QUEUE_MIN_TH)
			hinfo->te += len - NG_CAR_QUEUE_MIN_TH;

		/* If this is a first packet in the queue. */
		if (len == 0) {
			if (hinfo->conf.opt & NG_CAR_COUNT_PACKETS) {
				hinfo->tc -= 128;
			} else {
				hinfo->tc -= m->m_pkthdr.len;
			}

			/* Schedule queue processing. */
			ng_car_schedule(hinfo);
		}
	}

	/* Unlock queue mutex. */
	mtx_unlock(&hinfo->q_mtx);
}