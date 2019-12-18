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
typedef  void* uint32_t ;
struct timespec {void* tv_nsec; void* tv_sec; } ;
struct pvclock_wall_clock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvclock_read_wall_clock (struct pvclock_wall_clock*,void**,void**) ; 

void
pvclock_get_wallclock(struct pvclock_wall_clock *wc, struct timespec *ts)
{
	uint32_t sec, nsec;

	pvclock_read_wall_clock(wc, &sec, &nsec);
	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
}