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
struct timespec {int tv_nsec; unsigned long long tv_sec; } ;
struct thread {int dummy; } ;
typedef  scalar_t__ clockid_t ;

/* Variables and functions */
 scalar_t__ CLOCK_REALTIME ; 
 int EINVAL ; 
 int /*<<< orphan*/  PRIV_CLOCK_SETTIME ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  allow_insane_settime ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int settime (struct thread*,struct timeval*) ; 
 unsigned long long utc_offset () ; 

int
kern_clock_settime(struct thread *td, clockid_t clock_id, struct timespec *ats)
{
	struct timeval atv;
	int error;

	if ((error = priv_check(td, PRIV_CLOCK_SETTIME)) != 0)
		return (error);
	if (clock_id != CLOCK_REALTIME)
		return (EINVAL);
	if (ats->tv_nsec < 0 || ats->tv_nsec >= 1000000000 ||
	    ats->tv_sec < 0)
		return (EINVAL);
	if (!allow_insane_settime &&
	    (ats->tv_sec > 8000ULL * 365 * 24 * 60 * 60 ||
	    ats->tv_sec < utc_offset()))
		return (EINVAL);
	/* XXX Don't convert nsec->usec and back */
	TIMESPEC_TO_TIMEVAL(&atv, ats);
	error = settime(td, &atv);
	return (error);
}