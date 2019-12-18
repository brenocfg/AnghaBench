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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  timespecclear (struct timespec*) ; 
 int /*<<< orphan*/  xen_fetch_uptime (struct timespec*) ; 
 int /*<<< orphan*/  xen_fetch_wallclock (struct timespec*) ; 

__attribute__((used)) static int
xentimer_gettime(device_t dev, struct timespec *ts)
{
	struct timespec u_ts;

	timespecclear(ts);
	xen_fetch_wallclock(ts);
	xen_fetch_uptime(&u_ts);
	timespecadd(ts, &u_ts, ts);

	return (0);
}