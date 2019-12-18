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

/* Variables and functions */

__attribute__((used)) static void
scale_timespec(struct timespec *ts, int p)
{

	if (p == 0)
		return;

	ts->tv_sec /= p;
	ts->tv_nsec /= p;
}