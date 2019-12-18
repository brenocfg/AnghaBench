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
 int /*<<< orphan*/  O_RDONLY ; 
 char* _PATH_DEV ; 
 struct cmd* ctbl_main ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int mpfd ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int ac, char **av)
{
	const char *mountpt;
	struct cmd *c;
	int ch;

	mountpt = NULL;
	while ((ch = getopt(ac, av, "m:")) != -1)
		switch (ch) {
		case 'm':
			mountpt = optarg;
			break;
		default:
			usage();
		}
	ac -= optind;
	av += optind;
	if (ac < 1)
		usage();

	if (mountpt == NULL)
		mountpt = _PATH_DEV;
	mpfd = open(mountpt, O_RDONLY);
	if (mpfd == -1)
		err(1, "open: %s", mountpt);

	for (c = ctbl_main; c->name != NULL; ++c)
		if (strcmp(c->name, av[0]) == 0)
			exit((*c->handler)(ac, av));
	errx(1, "unknown command: %s", av[0]);
}