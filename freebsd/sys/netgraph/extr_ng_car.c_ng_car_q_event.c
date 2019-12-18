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
struct TYPE_4__ {int /*<<< orphan*/  passed_pkts; int /*<<< orphan*/  errors; } ;
struct hookinfo {scalar_t__ tc; size_t q_first; size_t q_last; TYPE_2__ conf; struct mbuf** q; TYPE_1__ stats; int /*<<< orphan*/  dest; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  hook_p ;

/* Variables and functions */
 int NG_CAR_COUNT_PACKETS ; 
 size_t NG_CAR_QUEUE_SIZE ; 
 struct hookinfo* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  ng_car_refillhook (struct hookinfo*) ; 
 int /*<<< orphan*/  ng_car_schedule (struct hookinfo*) ; 

void
ng_car_q_event(node_p node, hook_p hook, void *arg, int arg2)
{
	struct hookinfo	*hinfo = NG_HOOK_PRIVATE(hook);
	struct mbuf 	*m;
	int		error;

	/* Refill tokens for time we have slept. */
	ng_car_refillhook(hinfo);

	/* If we have some tokens */
	while (hinfo->tc >= 0) {

		/* Send packet. */
		m = hinfo->q[hinfo->q_first];
		NG_SEND_DATA_ONLY(error, hinfo->dest, m);
		if (error != 0)
			++hinfo->stats.errors;
		++hinfo->stats.passed_pkts;

		/* Get next one. */
		hinfo->q_first++;
		if (hinfo->q_first >= NG_CAR_QUEUE_SIZE)
			hinfo->q_first = 0;

		/* Stop if none left. */
		if (hinfo->q_first == hinfo->q_last)
			break;

		/* If we have more packet, try it. */
		m = hinfo->q[hinfo->q_first];
		if (hinfo->conf.opt & NG_CAR_COUNT_PACKETS) {
			hinfo->tc -= 128;
		} else {
			hinfo->tc -= m->m_pkthdr.len;
		}
	}

	/* If something left */
	if (hinfo->q_first != hinfo->q_last)
		/* Schedule queue processing. */
		ng_car_schedule(hinfo);
}