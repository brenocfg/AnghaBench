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
 int /*<<< orphan*/  LC_CTYPE ; 
 int all ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getstops (int /*<<< orphan*/ ) ; 
 int nstops ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int tabify (char*) ; 
 int* tabstops ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	int ch, failed;
	char *filename;

	setlocale(LC_CTYPE, "");

	nstops = 1;
	tabstops[0] = 8;
	while ((ch = getopt(argc, argv, "at:")) != -1) {
		switch (ch) {
		case 'a':	/* Un-expand all spaces, not just leading. */
			all = 1;
			break;
		case 't':	/* Specify tab list, implies -a. */
			getstops(optarg);
			all = 1;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	}
	argc -= optind;
	argv += optind;

	failed = 0;
	if (argc == 0)
		failed |= tabify("stdin");
	else {
		while ((filename = *argv++) != NULL) {
			if (freopen(filename, "r", stdin) == NULL) {
				warn("%s", filename);
				failed = 1;
			} else
				failed |= tabify(filename);
		}
	}
	exit(failed != 0);
}