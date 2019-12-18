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
 int Hflag ; 
 int /*<<< orphan*/  LC_TIME ; 
 int Tflag ; 
 int /*<<< orphan*/  UTXDB_ACTIVE ; 
 int aflag ; 
 int bflag ; 
 int /*<<< orphan*/  endutxent () ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  heading () ; 
 int mflag ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  process_utmp () ; 
 int qflag ; 
 int /*<<< orphan*/  quick () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setutxdb (int /*<<< orphan*/ ,char*) ; 
 int sflag ; 
 scalar_t__ strcmp (char*,char*) ; 
 int uflag ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  whoami () ; 

int
main(int argc, char *argv[])
{
	int ch;

	setlocale(LC_TIME, "");

	while ((ch = getopt(argc, argv, "HTabmqsu")) != -1) {
		switch (ch) {
		case 'H':		/* Write column headings */
			Hflag = 1;
			break;
		case 'T':		/* Show terminal state */
			Tflag = 1;
			break;
		case 'a':		/* Same as -bdlprtTu */
			aflag = bflag = Tflag = uflag = 1;
			break;
		case 'b':		/* Show date of the last reboot */
			bflag = 1;
			break;
		case 'm':		/* Show info about current terminal */
			mflag = 1;
			break;
		case 'q':		/* "Quick" mode */
			qflag = 1;
			break;
		case 's':		/* Show name, line, time */
			sflag = 1;
			break;
		case 'u':		/* Show idle time */
			uflag = 1;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	}
	argc -= optind;
	argv += optind;

	if (argc >= 2 && strcmp(argv[0], "am") == 0 &&
	    (strcmp(argv[1], "i") == 0 || strcmp(argv[1], "I") == 0)) {
		/* "who am i" or "who am I", equivalent to -m */
		mflag = 1;
		argc -= 2;
		argv += 2;
	}
	if (argc > 1)
		usage();

	if (*argv != NULL) {
		if (setutxdb(UTXDB_ACTIVE, *argv) != 0)
			err(1, "%s", *argv);
	}

	if (qflag)
		quick();
	else {
		if (sflag)
			Tflag = uflag = 0;
		if (Hflag)
			heading();
		if (mflag)
			whoami();
		else
			process_utmp();
	}

	endutxent();

	exit(0);
}