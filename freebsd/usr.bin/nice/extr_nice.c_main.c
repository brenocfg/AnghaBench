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
 long DEFNICE ; 
 scalar_t__ ENOENT ; 
 long INT_MAX ; 
 long INT_MIN ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 scalar_t__ asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (unsigned char) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 scalar_t__ setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(int argc, char *argv[])
{
	long niceness = DEFNICE;
	int ch;
	char *ep;

	/* Obsolescent syntax: -number, --number */
	if (argc >= 2 && argv[1][0] == '-' && (argv[1][1] == '-' ||
	    isdigit((unsigned char)argv[1][1])) && strcmp(argv[1], "--") != 0)
		if (asprintf(&argv[1], "-n%s", argv[1] + 1) < 0)
			err(1, "asprintf");

	while ((ch = getopt(argc, argv, "n:")) != -1) {
		switch (ch) {
		case 'n':
			errno = 0;
			niceness = strtol(optarg, &ep, 10);
			if (ep == optarg || *ep != '\0' || errno ||
			    niceness < INT_MIN || niceness > INT_MAX)
				errx(1, "%s: invalid nice value", optarg);
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	errno = 0;
	niceness += getpriority(PRIO_PROCESS, 0);
	if (errno)
		warn("getpriority");
	else if (setpriority(PRIO_PROCESS, 0, (int)niceness))
		warn("setpriority");
	execvp(*argv, argv);
	err(errno == ENOENT ? 127 : 126, "%s", *argv);
}