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
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gettime(struct timeval *tp)
{
#ifdef HAVE_CLOCK_GETTIME
	struct timespec	ts;

#ifdef HAVE_CLOCK_MONOTONIC      
	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
#else
	if (clock_gettime(CLOCK_REALTIME, &ts) == -1)
#endif
		return (-1);
	tp->tv_sec = ts.tv_sec;
	tp->tv_usec = ts.tv_nsec / 1000;
#else
	gettimeofday(tp, NULL);
#endif

	return (0);
}