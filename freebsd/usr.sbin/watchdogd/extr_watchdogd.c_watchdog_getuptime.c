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
 int /*<<< orphan*/  CLOCK_UPTIME_FAST ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  do_timedog ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
watchdog_getuptime(struct timespec *tp)
{
	int error;

	if (!do_timedog)
		return 0;

	error = clock_gettime(CLOCK_UPTIME_FAST, tp);
	if (error)
		warn("clock_gettime");
	return (error);
}