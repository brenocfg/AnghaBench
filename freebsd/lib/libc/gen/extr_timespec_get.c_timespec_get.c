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

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
#define  TIME_UTC 128 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

int
timespec_get(struct timespec *ts, int base)
{

	switch (base) {
	case TIME_UTC:
		if (clock_gettime(CLOCK_REALTIME, ts) == -1)
			return 0;
		break;
	default:
		return 0;
	}

	return base;
}