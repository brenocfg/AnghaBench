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
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME_PRECISE ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct timespec timespec_sub (struct timespec,struct timespec) ; 

__attribute__((used)) static struct timespec
wait_time(struct timespec ts)
{
	for (;;) {
		struct timespec w, cur;
		clock_gettime(CLOCK_REALTIME_PRECISE, &cur);
		w = timespec_sub(ts, cur);
		if (w.tv_sec < 0)
			return cur;
		else if (w.tv_sec > 0 || w.tv_nsec > 1000000)
			poll(NULL, 0, 1);
	}
}