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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
"test-ratelim [-v] [-n INT] [-d INT] [-c INT] [-g INT] [-t INT]\n\n"
"Pushes bytes through a number of possibly rate-limited connections, and\n"
"displays average throughput.\n\n"
"  -n INT: Number of connections to open (default: 30)\n"
"  -d INT: Duration of the test in seconds (default: 5 sec)\n");
	fprintf(stderr,
"  -c INT: Connection-rate limit applied to each connection in bytes per second\n"
"	   (default: None.)\n"
"  -g INT: Group-rate limit applied to sum of all usage in bytes per second\n"
"	   (default: None.)\n"
"  -G INT: drain INT bytes from the group limit every tick. (default: 0)\n"
"  -t INT: Granularity of timing, in milliseconds (default: 1000 msec)\n");
}