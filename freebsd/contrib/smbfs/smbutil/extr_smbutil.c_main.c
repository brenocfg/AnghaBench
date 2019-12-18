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
struct commands {int flags; int (* fn ) (int,char**) ;} ;

/* Variables and functions */
 int CMDFL_NO_KMOD ; 
 int EOF ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  help () ; 
 struct commands* lookupcmd (char*) ; 
 int optind ; 
 int optreset ; 
 scalar_t__ smb_lib_init () ; 
 int stub1 (int,char**) ; 
 int verbose ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

int
main(int argc, char *argv[])
{
	struct commands *cmd;
	char *cp;
	int opt;
#ifdef APPLE
        extern void dropsuid();

	dropsuid();
#endif /* APPLE */

	if (argc < 2)
		help();

	while ((opt = getopt(argc, argv, "hv")) != EOF) {
		switch (opt) {
		    case 'h':
			help();
			/*NOTREACHED */
		    case 'v':
			verbose = 1;
			break;
		    default:
			warnx("invalid option %c", opt);
			help();
			/*NOTREACHED */
		}
	}
	if (optind >= argc)
		help();

	cp = argv[optind];
	cmd = lookupcmd(cp);
	if (cmd == NULL)
		errx(EX_DATAERR, "unknown command %s", cp);

	if ((cmd->flags & CMDFL_NO_KMOD) == 0 && smb_lib_init() != 0)
		exit(1);

	argc -= optind;
	argv += optind;
	optind = optreset = 1;
	return cmd->fn(argc, argv);
}