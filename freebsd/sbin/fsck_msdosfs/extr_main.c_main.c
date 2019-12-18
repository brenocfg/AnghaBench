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
 int alwaysno ; 
 int alwaysyes ; 
 int checkfilesys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int preen ; 
 int /*<<< orphan*/  setcdevname (char*,int) ; 
 int skipclean ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ret = 0, erg;
	int ch;

	skipclean = 1;
	while ((ch = getopt(argc, argv, "CfFnpy")) != -1) {
		switch (ch) {
		case 'C': /* for fsck_ffs compatibility */
			break;
		case 'f':
			skipclean = 0;
			break;
		case 'F':
			/*
			 * We can never run in the background.  We must exit
			 * silently with a nonzero exit code so that fsck(8)
			 * can probe our support for -F.  The exit code
			 * doesn't really matter, but we use an unusual one
			 * in case someone tries -F directly.  The -F flag
			 * is intentionally left out of the usage message.
			 */
			exit(5);
		case 'n':
			alwaysno = 1;
			alwaysyes = 0;
			break;
		case 'y':
			alwaysyes = 1;
			alwaysno = 0;
			break;

		case 'p':
			preen = 1;
			break;

		default:
			usage();
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if (!argc)
		usage();

	while (--argc >= 0) {
		setcdevname(*argv, preen);
		erg = checkfilesys(*argv++);
		if (erg > ret)
			ret = erg;
	}

	return ret;
}