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
 int base64 ; 
 int /*<<< orphan*/  basename (char*) ; 
 int cflag ; 
 int decode () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int iflag ; 
 char* infile ; 
 int /*<<< orphan*/ * infp ; 
 int oflag ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  outfile ; 
 int pflag ; 
 int rflag ; 
 int sflag ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	int rval, ch;

	if (strcmp(basename(argv[0]), "b64decode") == 0)
		base64 = 1;

	while ((ch = getopt(argc, argv, "cimo:prs")) != -1) {
		switch (ch) {
		case 'c':
			if (oflag || rflag)
				usage();
			cflag = 1; /* multiple uudecode'd files */
			break;
		case 'i':
			iflag = 1; /* ask before override files */
			break;
		case 'm':
			base64 = 1;
			break;
		case 'o':
			if (cflag || pflag || rflag || sflag)
				usage();
			oflag = 1; /* output to the specified file */
			sflag = 1; /* do not strip pathnames for output */
			outfile = optarg; /* set the output filename */
			break;
		case 'p':
			if (oflag)
				usage();
			pflag = 1; /* print output to stdout */
			break;
		case 'r':
			if (cflag || oflag)
				usage();
			rflag = 1; /* decode raw data */
			break;
		case 's':
			if (oflag)
				usage();
			sflag = 1; /* do not strip pathnames for output */
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (*argv != NULL) {
		rval = 0;
		do {
			infp = fopen(infile = *argv, "r");
			if (infp == NULL) {
				warn("%s", *argv);
				rval = 1;
				continue;
			}
			rval |= decode();
			fclose(infp);
		} while (*++argv);
	} else {
		infile = "stdin";
		infp = stdin;
		rval = decode();
	}
	exit(rval);
}