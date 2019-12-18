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
struct timeval {int dummy; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;
typedef  int clockid_t ;

/* Variables and functions */
#define  CLOCK_MONOTONIC 141 
#define  CLOCK_MONOTONIC_FAST 140 
#define  CLOCK_MONOTONIC_PRECISE 139 
#define  CLOCK_PROCESS_CPUTIME_ID 138 
#define  CLOCK_PROF 137 
#define  CLOCK_REALTIME 136 
#define  CLOCK_REALTIME_FAST 135 
#define  CLOCK_REALTIME_PRECISE 134 
#define  CLOCK_SECOND 133 
#define  CLOCK_THREAD_CPUTIME_ID 132 
#define  CLOCK_UPTIME 131 
#define  CLOCK_UPTIME_FAST 130 
#define  CLOCK_UPTIME_PRECISE 129 
#define  CLOCK_VIRTUAL 128 
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  TIMEVAL_TO_TIMESPEC (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  calcru (struct proc*,struct timeval*,struct timeval*) ; 
 int get_cputime (struct thread*,int,struct timespec*) ; 
 int /*<<< orphan*/  get_process_cputime (struct proc*,struct timespec*) ; 
 int /*<<< orphan*/  get_thread_cputime (int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  getnanouptime (struct timespec*) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int /*<<< orphan*/  time_second ; 
 int /*<<< orphan*/  timevaladd (struct timeval*,struct timeval*) ; 

int
kern_clock_gettime(struct thread *td, clockid_t clock_id, struct timespec *ats)
{
	struct timeval sys, user;
	struct proc *p;

	p = td->td_proc;
	switch (clock_id) {
	case CLOCK_REALTIME:		/* Default to precise. */
	case CLOCK_REALTIME_PRECISE:
		nanotime(ats);
		break;
	case CLOCK_REALTIME_FAST:
		getnanotime(ats);
		break;
	case CLOCK_VIRTUAL:
		PROC_LOCK(p);
		PROC_STATLOCK(p);
		calcru(p, &user, &sys);
		PROC_STATUNLOCK(p);
		PROC_UNLOCK(p);
		TIMEVAL_TO_TIMESPEC(&user, ats);
		break;
	case CLOCK_PROF:
		PROC_LOCK(p);
		PROC_STATLOCK(p);
		calcru(p, &user, &sys);
		PROC_STATUNLOCK(p);
		PROC_UNLOCK(p);
		timevaladd(&user, &sys);
		TIMEVAL_TO_TIMESPEC(&user, ats);
		break;
	case CLOCK_MONOTONIC:		/* Default to precise. */
	case CLOCK_MONOTONIC_PRECISE:
	case CLOCK_UPTIME:
	case CLOCK_UPTIME_PRECISE:
		nanouptime(ats);
		break;
	case CLOCK_UPTIME_FAST:
	case CLOCK_MONOTONIC_FAST:
		getnanouptime(ats);
		break;
	case CLOCK_SECOND:
		ats->tv_sec = time_second;
		ats->tv_nsec = 0;
		break;
	case CLOCK_THREAD_CPUTIME_ID:
		get_thread_cputime(NULL, ats);
		break;
	case CLOCK_PROCESS_CPUTIME_ID:
		PROC_LOCK(p);
		get_process_cputime(p, ats);
		PROC_UNLOCK(p);
		break;
	default:
		if ((int)clock_id >= 0)
			return (EINVAL);
		return (get_cputime(td, clock_id, ats));
	}
	return (0);
}