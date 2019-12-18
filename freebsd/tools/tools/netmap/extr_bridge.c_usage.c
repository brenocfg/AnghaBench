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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
		"netmap bridge program: forward packets between two "
			"network interfaces\n"
		"    usage(1): bridge [-v] [-i ifa] [-i ifb] [-b burst] "
			"[-w wait_time] [-L]\n"
		"    usage(2): bridge [-v] [-w wait_time] [-L] "
			"[ifa [ifb [burst]]]\n"
		"\n"
		"    ifa and ifb are specified using the nm_open() syntax.\n"
		"    When ifb is missing (or is equal to ifa), bridge will\n"
		"    forward between between ifa and the host stack if -L\n"
		"    is not specified, otherwise loopback traffic on ifa.\n"
		"\n"
		"    example: bridge -w 10 -i netmap:eth3 -i netmap:eth1\n"
		);
	exit(1);
}