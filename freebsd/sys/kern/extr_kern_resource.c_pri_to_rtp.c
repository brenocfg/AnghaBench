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
struct thread {int /*<<< orphan*/  td_pri_class; scalar_t__ td_base_user_pri; } ;
struct rtprio {int /*<<< orphan*/  type; scalar_t__ prio; } ;

/* Variables and functions */
 int PRI_BASE (int /*<<< orphan*/ ) ; 
#define  PRI_IDLE 130 
 scalar_t__ PRI_MIN_IDLE ; 
 scalar_t__ PRI_MIN_REALTIME ; 
 scalar_t__ PRI_MIN_TIMESHARE ; 
#define  PRI_REALTIME 129 
#define  PRI_TIMESHARE 128 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

void
pri_to_rtp(struct thread *td, struct rtprio *rtp)
{

	thread_lock(td);
	switch (PRI_BASE(td->td_pri_class)) {
	case PRI_REALTIME:
		rtp->prio = td->td_base_user_pri - PRI_MIN_REALTIME;
		break;
	case PRI_TIMESHARE:
		rtp->prio = td->td_base_user_pri - PRI_MIN_TIMESHARE;
		break;
	case PRI_IDLE:
		rtp->prio = td->td_base_user_pri - PRI_MIN_IDLE;
		break;
	default:
		break;
	}
	rtp->type = td->td_pri_class;
	thread_unlock(td);
}