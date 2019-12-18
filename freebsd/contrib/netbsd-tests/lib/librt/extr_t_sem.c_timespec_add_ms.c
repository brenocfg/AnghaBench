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
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static inline void
timespec_add_ms(struct timespec *ts, int ms)
{
	ts->tv_nsec += ms * 1000*1000;
	if (ts->tv_nsec > 1000*1000*1000) {
		ts->tv_sec++;
		ts->tv_nsec -= 1000*1000*1000;
	}
}