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
 int /*<<< orphan*/  addgroup (char*) ; 
 int /*<<< orphan*/  doshell () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  euid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  geteuid () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  loginshell () ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * pwd ; 
 int /*<<< orphan*/  restoregrps () ; 
 scalar_t__ seteuid (int /*<<< orphan*/ ) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	int ch, login;

	if ((euid = geteuid()) != 0)
		warnx("need root permissions to function properly, check setuid bit");
	if (seteuid(getuid()) < 0)
		err(1, "seteuid");

	if ((pwd = getpwuid(getuid())) == NULL)
		errx(1, "unknown user");

	login = 0;
	while ((ch = getopt(argc, argv, "-l")) != -1) {
		switch (ch) {
		case '-':		/* Obsolescent */
		case 'l':
			login = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	switch (argc) {
	case 0:
		restoregrps();
		break;
	case 1:
		addgroup(*argv);
		break;
	default:
		usage();
	}

	if (seteuid(euid) < 0)
		err(1, "seteuid");
	if (setuid(getuid()) < 0)
		err(1, "setuid");

	if (login)
		loginshell();
	else
		doshell();

	/*NOTREACHED*/
	exit(1);
}