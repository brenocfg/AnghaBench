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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_time ; 
 int /*<<< orphan*/  warn (char*) ; 

int
priv_clock_settime_setup(int asroot, int injail, struct test *test)
{

	if (clock_gettime(CLOCK_REALTIME, &the_time) < 0) {
		warn("priv_clock_settime_setup: "
		    "clock_gettime(CLOCK_REALTIME)");
		return (-1);
	}
	return (0);
}