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
struct timespec {int tv_sec; int tv_nsec; } ;
struct thread {int dummy; } ;
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
 int cpu_tickrate () ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int tc_getfrequency () ; 

int
kern_clock_getres(struct thread *td, clockid_t clock_id, struct timespec *ts)
{

	ts->tv_sec = 0;
	switch (clock_id) {
	case CLOCK_REALTIME:
	case CLOCK_REALTIME_FAST:
	case CLOCK_REALTIME_PRECISE:
	case CLOCK_MONOTONIC:
	case CLOCK_MONOTONIC_FAST:
	case CLOCK_MONOTONIC_PRECISE:
	case CLOCK_UPTIME:
	case CLOCK_UPTIME_FAST:
	case CLOCK_UPTIME_PRECISE:
		/*
		 * Round up the result of the division cheaply by adding 1.
		 * Rounding up is especially important if rounding down
		 * would give 0.  Perfect rounding is unimportant.
		 */
		ts->tv_nsec = 1000000000 / tc_getfrequency() + 1;
		break;
	case CLOCK_VIRTUAL:
	case CLOCK_PROF:
		/* Accurately round up here because we can do so cheaply. */
		ts->tv_nsec = howmany(1000000000, hz);
		break;
	case CLOCK_SECOND:
		ts->tv_sec = 1;
		ts->tv_nsec = 0;
		break;
	case CLOCK_THREAD_CPUTIME_ID:
	case CLOCK_PROCESS_CPUTIME_ID:
	cputime:
		/* sync with cputick2usec */
		ts->tv_nsec = 1000000 / cpu_tickrate();
		if (ts->tv_nsec == 0)
			ts->tv_nsec = 1000;
		break;
	default:
		if ((int)clock_id < 0)
			goto cputime;
		return (EINVAL);
	}
	return (0);
}