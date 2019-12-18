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
typedef  scalar_t__ time_t ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
#define  EINVAL 129 
#define  ENXIO 128 
 int /*<<< orphan*/  ffclock_reset_clock (struct timespec*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_clocks (struct timespec*,int) ; 
 int /*<<< orphan*/  tc_setclock (struct timespec*) ; 

void
inittodr(time_t base)
{
	struct timespec ts;
	int error;

	error = read_clocks(&ts, false);

	/*
	 * Do not report errors from each clock; it is expected that some clocks
	 * cannot provide results in some situations.  Only report problems when
	 * no clocks could provide the time.
	 */
	if (error != 0) {
		switch (error) {
		case ENXIO:
			printf("Warning: no time-of-day clock registered, ");
			break;
		case EINVAL:
			printf("Warning: bad time from time-of-day clock, ");
			break;
		default:
			printf("Error reading time-of-day clock (%d), ", error);
			break;
		}
		printf("system time will not be set accurately\n");
		ts.tv_sec  = (base > 0) ? base : -1;
		ts.tv_nsec = 0;
	}

	if (ts.tv_sec >= 0) {
		tc_setclock(&ts);
#ifdef FFCLOCK
		ffclock_reset_clock(&ts);
#endif
	}
}