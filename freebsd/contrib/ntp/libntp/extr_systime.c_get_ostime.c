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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int GETTIMEOFDAY (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TIMEOFDAY ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getclock (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sys_tick ; 
 scalar_t__ trunc_os_clock ; 

__attribute__((used)) static inline void
get_ostime(
	struct timespec *	tsp
	)
{
	int	rc;
	long	ticks;

#if defined(HAVE_CLOCK_GETTIME)
	rc = clock_gettime(CLOCK_REALTIME, tsp);
#elif defined(HAVE_GETCLOCK)
	rc = getclock(TIMEOFDAY, tsp);
#else
	struct timeval		tv;

	rc = GETTIMEOFDAY(&tv, NULL);
	tsp->tv_sec = tv.tv_sec;
	tsp->tv_nsec = tv.tv_usec * 1000;
#endif
	if (rc < 0) {
		msyslog(LOG_ERR, "read system clock failed: %m (%d)",
			errno);
		exit(1);
	}

	if (trunc_os_clock) {
		ticks = (long)((tsp->tv_nsec * 1e-9) / sys_tick);
		tsp->tv_nsec = (long)(ticks * 1e9 * sys_tick);
	}
}