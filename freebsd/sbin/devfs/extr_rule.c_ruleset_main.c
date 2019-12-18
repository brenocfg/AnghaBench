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
typedef  int /*<<< orphan*/  devfs_rsnum ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFSIO_SUSE ; 
 int /*<<< orphan*/  eatonum (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpfd ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
ruleset_main(int ac, char **av)
{
	devfs_rsnum rsnum;
	int rv;

	setprogname("devfs ruleset");
	if (ac < 2)
		usage();
	rsnum = eatonum(av[1]);
	rv = ioctl(mpfd, DEVFSIO_SUSE, &rsnum);
	if (rv == -1)
		err(1, "ioctl DEVFSIO_SUSE");
	return (0);
}