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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  LC_ALL ; 
 int LONG_MAX ; 
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup ; 
 char* currfile ; 
 int /*<<< orphan*/  do_lineno (char const*) ; 
 int /*<<< orphan*/  do_rexp (char const*) ; 
 int doclean ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 char* get_line () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handlesig ; 
 int /*<<< orphan*/ * infile ; 
 char* infn ; 
 scalar_t__ isdigit (unsigned char) ; 
 int kflag ; 
 scalar_t__ lineno ; 
 int maxfiles ; 
 int /*<<< orphan*/ * newfile () ; 
 int nfiles ; 
 char const* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * overfile ; 
 char const* prefix ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ reps ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int sflag ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 void* strtol (char const*,char**,int) ; 
 long sufflen ; 
 int /*<<< orphan*/  toomuch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ truncofs ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct sigaction sa;
	long i;
	int ch;
	const char *expr;
	char *ep, *p;
	FILE *ofp;

	setlocale(LC_ALL, "");

	kflag = sflag = 0;
	prefix = "xx";
	sufflen = 2;
	while ((ch = getopt(argc, argv, "ksf:n:")) > 0) {
		switch (ch) {
		case 'f':
			prefix = optarg;
			break;
		case 'k':
			kflag = 1;
			break;
		case 'n':
			errno = 0;
			sufflen = strtol(optarg, &ep, 10);
			if (sufflen <= 0 || *ep != '\0' || errno != 0)
				errx(1, "%s: bad suffix length", optarg);
			break;
		case 's':
			sflag = 1;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	}

	if (sufflen + strlen(prefix) >= PATH_MAX)
		errx(1, "name too long");

	argc -= optind;
	argv += optind;

	if ((infn = *argv++) == NULL)
		usage();
	if (strcmp(infn, "-") == 0) {
		infile = stdin;
		infn = "stdin";
	} else if ((infile = fopen(infn, "r")) == NULL)
		err(1, "%s", infn);

	if (!kflag) {
		doclean = 1;
		atexit(cleanup);
		sa.sa_flags = 0;
		sa.sa_handler = handlesig;
		sigemptyset(&sa.sa_mask);
		sigaddset(&sa.sa_mask, SIGHUP);
		sigaddset(&sa.sa_mask, SIGINT);
		sigaddset(&sa.sa_mask, SIGTERM);
		sigaction(SIGHUP, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL);
	}

	lineno = 0;
	nfiles = 0;
	truncofs = 0;
	overfile = NULL;

	/* Ensure 10^sufflen < LONG_MAX. */
	for (maxfiles = 1, i = 0; i < sufflen; i++) {
		if (maxfiles > LONG_MAX / 10)
			errx(1, "%ld: suffix too long (limit %ld)",
			    sufflen, i);
		maxfiles *= 10;
	}

	/* Create files based on supplied patterns. */
	while (nfiles < maxfiles - 1 && (expr = *argv++) != NULL) {
		/* Look ahead & see if this pattern has any repetitions. */
		if (*argv != NULL && **argv == '{') {
			errno = 0;
			reps = strtol(*argv + 1, &ep, 10);
			if (reps < 0 || *ep != '}' || errno != 0)
				errx(1, "%s: bad repetition count", *argv + 1);
			argv++;
		} else
			reps = 0;

		if (*expr == '/' || *expr == '%') {
			do
				do_rexp(expr);
			while (reps-- != 0 && nfiles < maxfiles - 1);
		} else if (isdigit((unsigned char)*expr))
			do_lineno(expr);
		else
			errx(1, "%s: unrecognised pattern", expr);
	}

	/* Copy the rest into a new file. */
	if (!feof(infile)) {
		ofp = newfile();
		while ((p = get_line()) != NULL && fputs(p, ofp) != EOF)
			;
		if (!sflag)
			printf("%jd\n", (intmax_t)ftello(ofp));
		if (fclose(ofp) != 0)
			err(1, "%s", currfile);
	}

	toomuch(NULL, 0);
	doclean = 0;

	return (0);
}