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
struct devfs_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFSIO_RADD ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  in_rsnum ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct devfs_rule*) ; 
 int /*<<< orphan*/  mpfd ; 
 int /*<<< orphan*/  rulespec_infp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rulespec_intok (struct devfs_rule*,int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int
rule_add(int ac, char **av)
{
	struct devfs_rule dr;
	int rv;

	if (ac < 2)
		usage();
	if (strcmp(av[1], "-") == 0)
		rulespec_infp(stdin, DEVFSIO_RADD, in_rsnum);
	else {
		rulespec_intok(&dr, ac - 1, av + 1, in_rsnum);
		rv = ioctl(mpfd, DEVFSIO_RADD, &dr);
		if (rv == -1)
			err(1, "ioctl DEVFSIO_RADD");
	}
	return (0);
}