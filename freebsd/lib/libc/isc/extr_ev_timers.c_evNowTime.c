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
struct timespec {int dummy; } ;

/* Variables and functions */
 int CLOCK_MONOTONIC ; 
 int CLOCK_REALTIME ; 
 scalar_t__ __evOptMonoTime ; 
 scalar_t__ clock_gettime (int,struct timespec*) ; 
 struct timespec evConsTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct timespec evTimeSpec (struct timeval) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

struct timespec
evNowTime(void) {
	struct timeval now;
#ifdef CLOCK_REALTIME
	struct timespec tsnow;
	int m = CLOCK_REALTIME;

#ifdef CLOCK_MONOTONIC
	if (__evOptMonoTime)
		m = CLOCK_MONOTONIC;
#endif
	if (clock_gettime(m, &tsnow) == 0)
		return (tsnow);
#endif
	if (gettimeofday(&now, NULL) < 0)
		return (evConsTime(0, 0));
	return (evTimeSpec(now));
}