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
struct bw_meter {int bm_flags; int bm_time_hash; struct bw_meter* bm_time_next; } ;

/* Variables and functions */
 int BW_METER_BUCKETS ; 
 int BW_METER_LEQ ; 
 int /*<<< orphan*/  MFC_LOCK_ASSERT () ; 
 struct bw_meter** V_bw_meter_timers ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
unschedule_bw_meter(struct bw_meter *x)
{
    int time_hash;
    struct bw_meter *prev, *tmp;

    MFC_LOCK_ASSERT();

    if (!(x->bm_flags & BW_METER_LEQ))
	return;		/* XXX: we schedule timers only for "<=" entries */

    /*
     * Compute the timeout hash value and delete the entry
     */
    time_hash = x->bm_time_hash;
    if (time_hash >= BW_METER_BUCKETS)
	return;		/* Entry was not scheduled */

    for (prev = NULL, tmp = V_bw_meter_timers[time_hash];
	     tmp != NULL; prev = tmp, tmp = tmp->bm_time_next)
	if (tmp == x)
	    break;

    if (tmp == NULL)
	panic("unschedule_bw_meter: bw_meter entry not found");

    if (prev != NULL)
	prev->bm_time_next = x->bm_time_next;
    else
	V_bw_meter_timers[time_hash] = x->bm_time_next;

    x->bm_time_next = NULL;
    x->bm_time_hash = BW_METER_BUCKETS;
}