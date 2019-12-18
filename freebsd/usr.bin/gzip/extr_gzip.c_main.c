#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* zipped; int ziplen; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_SUFFIXES ; 
 int Nflag ; 
 int /*<<< orphan*/  OPT_LIST ; 
 int SUFFIX_MAXLEN ; 
 int cflag ; 
 int dflag ; 
 int /*<<< orphan*/  display_license () ; 
 int /*<<< orphan*/  display_version () ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_value ; 
 int fflag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  handle_pathname (char*) ; 
 int /*<<< orphan*/  handle_stdin () ; 
 int /*<<< orphan*/  handle_stdout () ; 
 int kflag ; 
 int lflag ; 
 int /*<<< orphan*/  longopts ; 
 int nflag ; 
 int numflag ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  prepend_gzip (char*,int*,char***) ; 
 int /*<<< orphan*/  print_list (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ qflag ; 
 int rflag ; 
 int /*<<< orphan*/  setup_signals () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 TYPE_1__* suffixes ; 
 int tflag ; 
 int /*<<< orphan*/  usage () ; 
 int vflag ; 

int
main(int argc, char **argv)
{
	const char *progname = getprogname();
#ifndef SMALL
	char *gzip;
	int len;
#endif
	int ch;

	setup_signals();

#ifndef SMALL
	if ((gzip = getenv("GZIP")) != NULL)
		prepend_gzip(gzip, &argc, &argv);
#endif

	/*
	 * XXX
	 * handle being called `gunzip', `zcat' and `gzcat'
	 */
	if (strcmp(progname, "gunzip") == 0)
		dflag = 1;
	else if (strcmp(progname, "zcat") == 0 ||
		 strcmp(progname, "gzcat") == 0)
		dflag = cflag = 1;

#ifdef SMALL
#define OPT_LIST "123456789cdhlV"
#else
#define OPT_LIST "123456789acdfhklLNnqrS:tVv"
#endif

	while ((ch = getopt_long(argc, argv, OPT_LIST, longopts, NULL)) != -1) {
		switch (ch) {
		case '1': case '2': case '3':
		case '4': case '5': case '6':
		case '7': case '8': case '9':
			numflag = ch - '0';
			break;
		case 'c':
			cflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'l':
			lflag = 1;
			dflag = 1;
			break;
		case 'V':
			display_version();
			/* NOTREACHED */
#ifndef SMALL
		case 'a':
			fprintf(stderr, "%s: option --ascii ignored on this system\n", progname);
			break;
		case 'f':
			fflag = 1;
			break;
		case 'k':
			kflag = 1;
			break;
		case 'L':
			display_license();
			/* NOT REACHED */
		case 'N':
			nflag = 0;
			Nflag = 1;
			break;
		case 'n':
			nflag = 1;
			Nflag = 0;
			break;
		case 'q':
			qflag = 1;
			break;
		case 'r':
			rflag = 1;
			break;
		case 'S':
			len = strlen(optarg);
			if (len != 0) {
				if (len > SUFFIX_MAXLEN)
					errx(1, "incorrect suffix: '%s': too long", optarg);
				suffixes[0].zipped = optarg;
				suffixes[0].ziplen = len;
			} else {
				suffixes[NUM_SUFFIXES - 1].zipped = "";
				suffixes[NUM_SUFFIXES - 1].ziplen = 0;
			}
			break;
		case 't':
			cflag = 1;
			tflag = 1;
			dflag = 1;
			break;
		case 'v':
			vflag = 1;
			break;
#endif
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argv += optind;
	argc -= optind;

	if (argc == 0) {
		if (dflag)	/* stdin mode */
			handle_stdin();
		else		/* stdout mode */
			handle_stdout();
	} else {
		do {
			handle_pathname(argv[0]);
		} while (*++argv);
	}
#ifndef SMALL
	if (qflag == 0 && lflag && argc > 1)
		print_list(-1, 0, "(totals)", 0);
#endif
	exit(exit_value);
}