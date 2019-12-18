#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; int /*<<< orphan*/  (* load ) () ;} ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 int getopt (int,char**,char*) ; 
 int nitems (TYPE_1__*) ; 
 int optind ; 
 int optreset ; 
 TYPE_1__* pnp_buses ; 
 scalar_t__ pnp_dump_flag ; 
 scalar_t__ pnp_verbose_flag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int
command_pnpautoload(int argc, char *argv[])
{
	int i;
	int verbose;
	int ch, match;

	pnp_verbose_flag = 0;
	pnp_dump_flag = 0;
	verbose = 0;
	optind = 1;
	optreset = 1;
	match = 0;
	while ((ch = getopt(argc, argv, "v")) != -1) {
		switch(ch) {
		case 'v':
			verbose = 1;
			break;
		case '?':
		default:
			/* getopt has already reported an error */
			return(CMD_OK);
		}
	}
	argv += (optind - 1);
	argc -= (optind - 1);

	if (argc > 2)
		return (CMD_ERROR);

	for (i = 0; i < nitems(pnp_buses); i++) {
		if (argc == 2 && strcmp(argv[1], pnp_buses[i].name) != 0) {
			if (verbose)
				printf("Skipping bus %s\n", pnp_buses[i].name);
			continue;
		}
		if (verbose)
			printf("Autoloading modules for simplebus\n");
		pnp_buses[i].load();
		match = 1;
	}
	if (match == 0)
		printf("Unsupported bus %s\n", argv[1]);

	return (CMD_OK);
}