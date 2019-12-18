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
typedef  int time_t ;
struct timezone {int dummy; } ;
typedef  int TimeType ;

/* Variables and functions */
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_IEVENT ; 
 int /*<<< orphan*/  gettimeofday (int*,struct timezone*) ; 
 int time (int*) ; 

__attribute__((used)) static long
_nc_gettime(TimeType * t0, int first)
{
    long res;

#if PRECISE_GETTIME
    TimeType t1;
    gettimeofday(&t1, (struct timezone *) 0);
    if (first) {
	*t0 = t1;
	res = 0;
    } else {
	/* .tv_sec and .tv_usec are unsigned, be careful when subtracting */
	if (t0->tv_usec > t1.tv_usec) {
	    t1.tv_usec += 1000000;	/* Convert 1s in 1e6 microsecs */
	    t1.tv_sec--;
	}
	res = (t1.tv_sec - t0->tv_sec) * 1000
	    + (t1.tv_usec - t0->tv_usec) / 1000;
    }
#else
    time_t t1 = time((time_t *) 0);
    if (first) {
	*t0 = t1;
    }
    res = (t1 - *t0) * 1000;
#endif
    TR(TRACE_IEVENT, ("%s time: %ld msec", first ? "get" : "elapsed", res));
    return res;
}