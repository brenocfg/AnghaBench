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
 int BUFSIZ ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int EX_OK ; 
 int action (char*) ; 
 int /*<<< orphan*/  dump_config () ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  stdin ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int do_stdin, opt;
	int aflag, rv;
	char *cp;
	char line[BUFSIZ];

	aflag = do_stdin = 0;
	rv = EX_OK;
	while ((opt = getopt(argc, argv, "-a")) != -1) {
		switch (opt) {
		case '-':
			if (aflag)
				usage();
			do_stdin = 1;
			break;
		case 'a':
			if (do_stdin)
				usage();
			aflag = 1;
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (aflag) {
		if (argc != 0)
			usage();
		dump_config();
	} else {
		if (do_stdin) {
			while (fgets(line, BUFSIZ, stdin) != NULL &&
			    rv == EX_OK) {
				if (line[0] == '\n')
					continue;
				if ((cp = strrchr(line, '\n')) != NULL)
					*cp = '\0';
				rv = action(line);
			}
			if (ferror(stdin))
				err(EX_NOINPUT, "stdin");
		} else {
			if (argc == 0)
				usage();
			while (argc && rv == EX_OK) {
				rv = action(*argv);
				++argv;
				--argc;
			}
		}
	}
	return (rv);
}