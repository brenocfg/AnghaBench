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
 int /*<<< orphan*/  dump_lockstate (char*) ; 
 int /*<<< orphan*/  dump_openstate () ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ modfind (char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ch, openstate;
	char *lockfile;

	if (modfind("nfsd") < 0)
		errx(1, "nfsd not loaded - self terminating");
	openstate = 0;
	lockfile = NULL;
	while ((ch = getopt(argc, argv, "ol:")) != -1)
		switch (ch) {
		case 'o':
			openstate = 1;
			break;
		case 'l':
			lockfile = optarg;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (openstate == 0 && lockfile == NULL)
		openstate = 1;
	else if (openstate != 0 && lockfile != NULL)
		errx(1, "-o and -l cannot both be specified");

	/*
	 * For -o, dump all open/lock state.
	 * For -l, dump lock state for that file.
	 */
	if (openstate != 0)
		dump_openstate();
	else
		dump_lockstate(lockfile);
	exit(0);
}