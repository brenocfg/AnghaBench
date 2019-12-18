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
struct timezone {int /*<<< orphan*/  tz_dsttime; int /*<<< orphan*/  tz_minuteswest; } ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timeb {int millitm; int /*<<< orphan*/  dstflag; int /*<<< orphan*/  timezone; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 scalar_t__ gettimeofday (struct timeval*,struct timezone*) ; 

int
ftime(struct timeb *tbp)
{
	struct timezone tz;
	struct timeval t;

	if (gettimeofday(&t, &tz) < 0)
		return (-1);
	tbp->millitm = t.tv_usec / 1000;
	tbp->time = t.tv_sec;
	tbp->timezone = tz.tz_minuteswest;
	tbp->dstflag = tz.tz_dsttime;

	return (0);
}