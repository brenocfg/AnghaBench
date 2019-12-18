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
struct cmd {int /*<<< orphan*/  (* handler ) (int,char**) ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct cmd* ctbl_rule ; 
 int /*<<< orphan*/  eatonum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  in_rsnum ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 
 int /*<<< orphan*/  usage () ; 

int
rule_main(int ac, char **av)
{
	struct cmd *c;
	int ch;

	setprogname("devfs rule");
	optreset = optind = 1;
	while ((ch = getopt(ac, av, "s:")) != -1)
		switch (ch) {
		case 's':
			in_rsnum = eatonum(optarg);
			break;
		default:
			usage();
		}
	ac -= optind;
	av += optind;
	if (ac < 1)
		usage();

	for (c = ctbl_rule; c->name != NULL; ++c)
		if (strcmp(c->name, av[0]) == 0)
			exit((*c->handler)(ac, av));
	errx(1, "unknown command: %s", av[0]);
}