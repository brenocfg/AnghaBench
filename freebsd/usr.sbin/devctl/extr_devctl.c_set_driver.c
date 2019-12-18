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
 scalar_t__ devctl_set_driver (char*,char*,int) ; 
 int /*<<< orphan*/  err (int,char*,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  set_driver_usage () ; 

__attribute__((used)) static int
set_driver(int ac, char **av)
{
	bool force;
	int ch;

	force = false;
	while ((ch = getopt(ac, av, "f")) != -1)
		switch (ch) {
		case 'f':
			force = true;
			break;
		default:
			set_driver_usage();
		}
	ac -= optind;
	av += optind;

	if (ac != 2)
		set_driver_usage();
	if (devctl_set_driver(av[0], av[1], force) < 0)
		err(1, "Failed to set %s driver to %s", av[0], av[1]);
	return (0);
}