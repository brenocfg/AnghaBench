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
typedef  scalar_t__ u_char ;
struct thread {scalar_t__ td_pri_class; scalar_t__ td_user_pri; } ;
struct rtprio {scalar_t__ prio; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PRI_MAX_TIMESHARE ; 
 scalar_t__ PRI_MIN_IDLE ; 
 scalar_t__ PRI_MIN_REALTIME ; 
 scalar_t__ PRI_MIN_TIMESHARE ; 
 int RTP_PRIO_BASE (int /*<<< orphan*/ ) ; 
#define  RTP_PRIO_IDLE 130 
 scalar_t__ RTP_PRIO_MAX ; 
#define  RTP_PRIO_NORMAL 129 
#define  RTP_PRIO_REALTIME 128 
 scalar_t__ TD_ON_UPILOCK (struct thread*) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  sched_class (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_prio (struct thread*,scalar_t__) ; 
 int /*<<< orphan*/  sched_user_prio (struct thread*,scalar_t__) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int /*<<< orphan*/  umtx_pi_adjust (struct thread*,scalar_t__) ; 

int
rtp_to_pri(struct rtprio *rtp, struct thread *td)
{
	u_char  newpri, oldclass, oldpri;

	switch (RTP_PRIO_BASE(rtp->type)) {
	case RTP_PRIO_REALTIME:
		if (rtp->prio > RTP_PRIO_MAX)
			return (EINVAL);
		newpri = PRI_MIN_REALTIME + rtp->prio;
		break;
	case RTP_PRIO_NORMAL:
		if (rtp->prio > (PRI_MAX_TIMESHARE - PRI_MIN_TIMESHARE))
			return (EINVAL);
		newpri = PRI_MIN_TIMESHARE + rtp->prio;
		break;
	case RTP_PRIO_IDLE:
		if (rtp->prio > RTP_PRIO_MAX)
			return (EINVAL);
		newpri = PRI_MIN_IDLE + rtp->prio;
		break;
	default:
		return (EINVAL);
	}

	thread_lock(td);
	oldclass = td->td_pri_class;
	sched_class(td, rtp->type);	/* XXX fix */
	oldpri = td->td_user_pri;
	sched_user_prio(td, newpri);
	if (td->td_user_pri != oldpri && (oldclass != RTP_PRIO_NORMAL ||
	    td->td_pri_class != RTP_PRIO_NORMAL))
		sched_prio(td, td->td_user_pri);
	if (TD_ON_UPILOCK(td) && oldpri != newpri) {
		critical_enter();
		thread_unlock(td);
		umtx_pi_adjust(td, oldpri);
		critical_exit();
	} else
		thread_unlock(td);
	return (0);
}