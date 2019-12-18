#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_5__ {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_7__ {int qcnt; int qmax; int borrows; int delays; TYPE_2__ drop_cnt; TYPE_1__ xmit_cnt; } ;
struct TYPE_8__ {TYPE_3__ cbq_stats; } ;
struct queue_stats {int avgn; int avg_packets; int avg_bytes; TYPE_4__ data; } ;

/* Variables and functions */
 int STAT_INTERVAL ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 char* rate2str (int) ; 

void
print_cbqstats(struct queue_stats cur)
{
	printf("  [ pkts: %10llu  bytes: %10llu  "
	    "dropped pkts: %6llu bytes: %6llu ]\n",
	    (unsigned long long)cur.data.cbq_stats.xmit_cnt.packets,
	    (unsigned long long)cur.data.cbq_stats.xmit_cnt.bytes,
	    (unsigned long long)cur.data.cbq_stats.drop_cnt.packets,
	    (unsigned long long)cur.data.cbq_stats.drop_cnt.bytes);
	printf("  [ qlength: %3d/%3d  borrows: %6u  suspends: %6u ]\n",
	    cur.data.cbq_stats.qcnt, cur.data.cbq_stats.qmax,
	    cur.data.cbq_stats.borrows, cur.data.cbq_stats.delays);

	if (cur.avgn < 2)
		return;

	printf("  [ measured: %7.1f packets/s, %s/s ]\n",
	    cur.avg_packets / STAT_INTERVAL,
	    rate2str((8 * cur.avg_bytes) / STAT_INTERVAL));
}