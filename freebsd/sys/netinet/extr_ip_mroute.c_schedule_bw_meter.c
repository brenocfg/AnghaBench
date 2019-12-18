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
struct timeval {int dummy; } ;
struct TYPE_2__ {scalar_t__ b_bytes; scalar_t__ b_packets; } ;
struct bw_meter {int bm_flags; int bm_time_hash; struct bw_meter* bm_time_next; TYPE_1__ bm_measured; struct timeval bm_start_time; } ;

/* Variables and functions */
 int BW_METER_LEQ ; 
 int /*<<< orphan*/  BW_METER_TIMEHASH (struct bw_meter*,int) ; 
 int BW_METER_UPCALL_DELIVERED ; 
 int /*<<< orphan*/  MFC_LOCK_ASSERT () ; 
 struct bw_meter** V_bw_meter_timers ; 

__attribute__((used)) static void
schedule_bw_meter(struct bw_meter *x, struct timeval *nowp)
{
    int time_hash;

    MFC_LOCK_ASSERT();

    if (!(x->bm_flags & BW_METER_LEQ))
	return;		/* XXX: we schedule timers only for "<=" entries */

    /*
     * Reset the bw_meter entry
     */
    x->bm_start_time = *nowp;
    x->bm_measured.b_packets = 0;
    x->bm_measured.b_bytes = 0;
    x->bm_flags &= ~BW_METER_UPCALL_DELIVERED;

    /*
     * Compute the timeout hash value and insert the entry
     */
    BW_METER_TIMEHASH(x, time_hash);
    x->bm_time_next = V_bw_meter_timers[time_hash];
    V_bw_meter_timers[time_hash] = x;
    x->bm_time_hash = time_hash;
}