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
struct mfiutil_command {int (* handler ) (int,char**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (int,char**) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

int
mfi_table_handler(struct mfiutil_command **start, struct mfiutil_command **end,
    int ac, char **av)
{
	struct mfiutil_command **cmd;

	if (ac < 2) {
		warnx("The %s command requires a sub-command.", av[0]);
		return (EINVAL);
	}
	for (cmd = start; cmd < end; cmd++) {
		if (strcmp((*cmd)->name, av[1]) == 0)
			return ((*cmd)->handler(ac - 1, av + 1));
	}

	warnx("%s is not a valid sub-command of %s.", av[1], av[0]);
	return (ENOENT);
}