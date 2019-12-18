#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int length; int len_bytes; int tot_bytes; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  drops; } ;
struct TYPE_10__ {TYPE_4__ ni; } ;
struct TYPE_6__ {int length; int len_bytes; int tot_bytes; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  drops; } ;
struct TYPE_7__ {TYPE_1__ ni; } ;
struct fq_pie_si {TYPE_5__ _si; TYPE_2__ main_q; } ;
struct TYPE_8__ {int length; int len_bytes; int tot_bytes; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  drops; } ;
struct fq_pie_flow {TYPE_3__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_pkt_drop ; 

__attribute__((used)) __inline static void
fq_update_stats(struct fq_pie_flow *q, struct fq_pie_si *si, int len,
	int drop)
{
	int inc = 0;

	if (len < 0) 
		inc = -1;
	else if (len > 0)
		inc = 1;

	if (drop) {
		si->main_q.ni.drops ++;
		q->stats.drops ++;
		si->_si.ni.drops ++;
		io_pkt_drop ++;
	} 

	if (!drop || (drop && len < 0)) {
		/* Update stats for the main queue */
		si->main_q.ni.length += inc;
		si->main_q.ni.len_bytes += len;

		/*update sub-queue stats */
		q->stats.length += inc;
		q->stats.len_bytes += len;

		/*update scheduler instance stats */
		si->_si.ni.length += inc;
		si->_si.ni.len_bytes += len;
	}

	if (inc > 0) {
		si->main_q.ni.tot_bytes += len;
		si->main_q.ni.tot_pkts ++;
		
		q->stats.tot_bytes +=len;
		q->stats.tot_pkts++;
		
		si->_si.ni.tot_bytes +=len;
		si->_si.ni.tot_pkts ++;
	}

}