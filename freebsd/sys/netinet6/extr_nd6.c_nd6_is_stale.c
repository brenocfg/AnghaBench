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
typedef  scalar_t__ time_t ;
struct llentry {int r_skip_req; long lle_remtime; scalar_t__ lle_hittime; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLE_REQ_LOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REQ_UNLOCK (struct llentry*) ; 
 scalar_t__ MIN (int,int) ; 
 int V_nd6_delay ; 
 int V_nd6_gctimer ; 
 long hz ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static int
nd6_is_stale(struct llentry *lle, long *pdelay, int *do_switch)
{
	int nd_delay, nd_gctimer, r_skip_req;
	time_t lle_hittime;
	long delay;

	*do_switch = 0;
	nd_gctimer = V_nd6_gctimer;
	nd_delay = V_nd6_delay;

	LLE_REQ_LOCK(lle);
	r_skip_req = lle->r_skip_req;
	lle_hittime = lle->lle_hittime;
	LLE_REQ_UNLOCK(lle);

	if (r_skip_req > 0) {

		/*
		 * Nonzero r_skip_req value was set upon entering
		 * STALE state. Since value was not changed, no
		 * packets were passed using this lle. Ask for
		 * timer reschedule and keep STALE state.
		 */
		delay = (long)(MIN(nd_gctimer, nd_delay));
		delay *= hz;
		if (lle->lle_remtime > delay)
			lle->lle_remtime -= delay;
		else {
			delay = lle->lle_remtime;
			lle->lle_remtime = 0;
		}

		if (delay == 0) {

			/*
			 * The original ng6_gctime timeout ended,
			 * no more rescheduling.
			 */
			return (0);
		}

		*pdelay = delay;
		return (1);
	}

	/*
	 * Packet received. Verify timestamp
	 */
	delay = (long)(time_uptime - lle_hittime);
	if (delay < nd_delay) {

		/*
		 * V_nd6_delay still not passed since the first
		 * hit in STALE state.
		 * Reshedule timer and return.
		 */
		*pdelay = (long)(nd_delay - delay) * hz;
		return (1);
	}

	/* Request switching to probe */
	*do_switch = 1;
	return (0);
}