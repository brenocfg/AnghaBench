#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
struct TYPE_13__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_14__ {TYPE_10__ cl_xmitcnt; } ;
struct TYPE_23__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_24__ {TYPE_8__ xmit_cnt; } ;
struct TYPE_21__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_22__ {TYPE_6__ xmit_cnt; } ;
struct TYPE_19__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_20__ {TYPE_4__ xmitcnt; } ;
struct TYPE_17__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_18__ {TYPE_2__ xmit_cnt; } ;
struct TYPE_15__ {TYPE_11__ codel_stats; TYPE_9__ fairq_stats; TYPE_7__ hfsc_stats; TYPE_5__ priq_stats; TYPE_3__ cbq_stats; } ;
struct queue_stats {int avgn; scalar_t__ prev_bytes; scalar_t__ prev_packets; int avg_bytes; int avg_packets; TYPE_12__ data; } ;
struct TYPE_16__ {scalar_t__ qid; int scheduler; } ;
struct pf_altq_node {TYPE_1__ altq; struct queue_stats qstats; } ;

/* Variables and functions */
#define  ALTQT_CBQ 132 
#define  ALTQT_CODEL 131 
#define  ALTQT_FAIRQ 130 
#define  ALTQT_HFSC 129 
#define  ALTQT_PRIQ 128 
 int AVGN_MAX ; 

void
update_avg(struct pf_altq_node *a)
{
	struct queue_stats	*qs;
	u_int64_t		 b, p;
	int			 n;

	if (a->altq.qid == 0 && a->altq.scheduler != ALTQT_CODEL)
		return;

	qs = &a->qstats;
	n = qs->avgn;

	switch (a->altq.scheduler) {
	case ALTQT_CBQ:
		b = qs->data.cbq_stats.xmit_cnt.bytes;
		p = qs->data.cbq_stats.xmit_cnt.packets;
		break;
	case ALTQT_PRIQ:
		b = qs->data.priq_stats.xmitcnt.bytes;
		p = qs->data.priq_stats.xmitcnt.packets;
		break;
	case ALTQT_HFSC:
		b = qs->data.hfsc_stats.xmit_cnt.bytes;
		p = qs->data.hfsc_stats.xmit_cnt.packets;
		break;
	case ALTQT_FAIRQ:
		b = qs->data.fairq_stats.xmit_cnt.bytes;
		p = qs->data.fairq_stats.xmit_cnt.packets;
		break;
	case ALTQT_CODEL:
		b = qs->data.codel_stats.cl_xmitcnt.bytes;
		p = qs->data.codel_stats.cl_xmitcnt.packets;
		break;
	default:
		b = 0;
		p = 0;
		break;
	}

	if (n == 0) {
		qs->prev_bytes = b;
		qs->prev_packets = p;
		qs->avgn++;
		return;
	}

	if (b >= qs->prev_bytes)
		qs->avg_bytes = ((qs->avg_bytes * (n - 1)) +
		    (b - qs->prev_bytes)) / n;

	if (p >= qs->prev_packets)
		qs->avg_packets = ((qs->avg_packets * (n - 1)) +
		    (p - qs->prev_packets)) / n;

	qs->prev_bytes = b;
	qs->prev_packets = p;
	if (n < AVGN_MAX)
		qs->avgn++;
}