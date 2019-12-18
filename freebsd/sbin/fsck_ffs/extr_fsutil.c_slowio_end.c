#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_2__ {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int slowio_delay_usec ; 
 scalar_t__ slowio_pollcnt ; 
 TYPE_1__ slowio_starttime ; 
 int /*<<< orphan*/  usleep (int) ; 

void
slowio_end()
{
	struct timeval tv;
	int delay_usec;

	if (slowio_pollcnt != 0)
		return;

	/* Update the slowdown interval. */
	gettimeofday(&tv, NULL);
	delay_usec = (tv.tv_sec - slowio_starttime.tv_sec) * 1000000 +
	    (tv.tv_usec - slowio_starttime.tv_usec);
	if (delay_usec < 64)
		delay_usec = 64;
	if (delay_usec > 2500000)
		delay_usec = 2500000;
	slowio_delay_usec = (slowio_delay_usec * 63 + delay_usec) >> 6;
	/* delay by 8 times the average IO delay */
	if (slowio_delay_usec > 64)
		usleep(slowio_delay_usec * 8);
}