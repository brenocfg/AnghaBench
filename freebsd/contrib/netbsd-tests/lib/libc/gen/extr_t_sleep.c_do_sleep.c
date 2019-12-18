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
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 

int
do_sleep(struct timespec *delay, struct timespec *remain)
{
	struct timeval tv;

	TIMESPEC_TO_TIMEVAL(&tv, delay);
	remain->tv_sec = sleep(delay->tv_sec);
	remain->tv_nsec = 0;

	return 0;
}