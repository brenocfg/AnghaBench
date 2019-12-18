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
struct timespec {unsigned long long tv_sec; unsigned long long tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 unsigned long long UM_NSEC_PER_SEC ; 
 scalar_t__ clock_nanosleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deliver_alarm () ; 

void os_idle_sleep(unsigned long long nsecs)
{
	struct timespec ts = {
		.tv_sec  = nsecs / UM_NSEC_PER_SEC,
		.tv_nsec = nsecs % UM_NSEC_PER_SEC
	};

	/*
	 * Relay the signal if clock_nanosleep is interrupted.
	 */
	if (clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL))
		deliver_alarm();
}