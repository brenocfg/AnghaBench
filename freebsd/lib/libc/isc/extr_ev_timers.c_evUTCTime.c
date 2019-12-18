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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 struct timespec evConsTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct timespec evTimeSpec (struct timeval) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

struct timespec
evUTCTime(void) {
	struct timeval now;
#ifdef CLOCK_REALTIME
	struct timespec tsnow;
	if (clock_gettime(CLOCK_REALTIME, &tsnow) == 0)
		return (tsnow);
#endif
	if (gettimeofday(&now, NULL) < 0)
		return (evConsTime(0, 0));
	return (evTimeSpec(now));
}