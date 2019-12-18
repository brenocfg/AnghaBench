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
struct timeval {double tv_sec; double tv_usec; } ;
struct cpu_usage_timer {double ticksBegin; int /*<<< orphan*/  timeBegin; int /*<<< orphan*/  kerneltimeBegin; int /*<<< orphan*/  usertimeBegin; int /*<<< orphan*/  thread; } ;
typedef  double clock_t ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 scalar_t__ CLOCKS_PER_SEC ; 
 int GetThreadTimes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double clock () ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timersub (struct timeval*,int /*<<< orphan*/ *,struct timeval*) ; 
 double filetime_diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
get_cpu_usage(struct cpu_usage_timer *timer, double *secElapsedOut,
    double *secUsedOut, double *usageOut)
{
#ifdef _WIN32
	double usertime_seconds, kerneltime_seconds;
	FILETIME createtime, exittime, usertimeEnd, kerneltimeEnd;
	int r;
#else
	clock_t ticksEnd;
#endif
	struct timeval timeEnd, timeDiff;
	double secondsPassed, secondsUsed;

#ifdef _WIN32
	r = GetThreadTimes(timer->thread, &createtime, &exittime,
	    &usertimeEnd, &kerneltimeEnd);
	if (r==0) printf("GetThreadTimes failed.");
	usertime_seconds = filetime_diff(&timer->usertimeBegin, &usertimeEnd);
	kerneltime_seconds = filetime_diff(&timer->kerneltimeBegin, &kerneltimeEnd);
	secondsUsed = kerneltime_seconds + usertime_seconds;
#else
	ticksEnd = clock();
	secondsUsed = (ticksEnd - timer->ticksBegin) / (double)CLOCKS_PER_SEC;
#endif
	evutil_gettimeofday(&timeEnd, NULL);
	evutil_timersub(&timeEnd, &timer->timeBegin, &timeDiff);
	secondsPassed = timeDiff.tv_sec + (timeDiff.tv_usec / 1.0e6);

	*secElapsedOut = secondsPassed;
	*secUsedOut = secondsUsed;
	*usageOut = secondsUsed / secondsPassed;
}