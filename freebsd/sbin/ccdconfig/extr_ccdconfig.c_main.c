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
#define  CCD_CONFIG 132 
#define  CCD_CONFIGALL 131 
#define  CCD_DUMP 130 
#define  CCD_UNCONFIG 129 
#define  CCD_UNCONFIGALL 128 
 int /*<<< orphan*/  ccdconf ; 
 int /*<<< orphan*/  do_all (int) ; 
 int /*<<< orphan*/  do_single (int,char**,int) ; 
 int /*<<< orphan*/  dump_ccd (int,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ kldload (char*) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(int argc, char *argv[])
{
	int ch, options = 0, action = CCD_CONFIG;

	while ((ch = getopt(argc, argv, "cCf:guUv")) != -1) {
		switch (ch) {
		case 'c':
			action = CCD_CONFIG;
			++options;
			break;

		case 'C':
			action = CCD_CONFIGALL;
			++options;
			break;

		case 'f':
			ccdconf = optarg;
			break;

		case 'g':
			action = CCD_DUMP;
			break;

		case 'u':
			action = CCD_UNCONFIG;
			++options;
			break;

		case 'U':
			action = CCD_UNCONFIGALL;
			++options;
			break;

		case 'v':
			verbose = 1;
			break;

		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (options > 1)
		usage();

	if (modfind("g_ccd") < 0) {
		/* Not present in kernel, try loading it */
		if (kldload("geom_ccd") < 0 || modfind("g_ccd") < 0)
			warn("geom_ccd module not available!");
	}

	switch (action) {
		case CCD_CONFIG:
		case CCD_UNCONFIG:
			exit(do_single(argc, argv, action));
			/* NOTREACHED */

		case CCD_CONFIGALL:
		case CCD_UNCONFIGALL:
			exit(do_all(action));
			/* NOTREACHED */

		case CCD_DUMP:
			exit(dump_ccd(argc, argv));
			/* NOTREACHED */
	}
	/* NOTREACHED */
	return (0);
}