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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  LC_ALL ; 
 unsigned long TIOCGETA ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cap_rights_is_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_rights_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_ioctls_limit (int /*<<< orphan*/ ,unsigned long*,int) ; 
 scalar_t__ caph_rights_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cflag ; 
 int /*<<< orphan*/ * convert (char*) ; 
 int dflag ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file (char const*,char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iflag ; 
 int inlcmp (char*,char*) ; 
 int /*<<< orphan*/  long_opts ; 
 void* numchars ; 
 void* numfields ; 
 int /*<<< orphan*/  obsolete (char**) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 scalar_t__ repeats ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strtol (int /*<<< orphan*/ ,char**,int) ; 
 int uflag ; 
 int /*<<< orphan*/  usage () ; 
 int wcscoll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
main (int argc, char *argv[])
{
	wchar_t *tprev, *tthis;
	FILE *ifp, *ofp;
	int ch, comp;
	size_t prevbuflen, thisbuflen, b1;
	char *prevline, *thisline, *p;
	const char *ifn;
	cap_rights_t rights;

	(void) setlocale(LC_ALL, "");

	obsolete(argv);
	while ((ch = getopt_long(argc, argv, "+cdif:s:u", long_opts,
	    NULL)) != -1)
		switch (ch) {
		case 'c':
			cflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'i':
			iflag = 1;
			break;
		case 'f':
			numfields = strtol(optarg, &p, 10);
			if (numfields < 0 || *p)
				errx(1, "illegal field skip value: %s", optarg);
			break;
		case 's':
			numchars = strtol(optarg, &p, 10);
			if (numchars < 0 || *p)
				errx(1, "illegal character skip value: %s", optarg);
			break;
		case 'u':
			uflag = 1;
			break;
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc > 2)
		usage();

	ifp = stdin;
	ifn = "stdin";
	ofp = stdout;
	if (argc > 0 && strcmp(argv[0], "-") != 0)
		ifp = file(ifn = argv[0], "r");
	cap_rights_init(&rights, CAP_FSTAT, CAP_READ);
	if (caph_rights_limit(fileno(ifp), &rights) < 0)
		err(1, "unable to limit rights for %s", ifn);
	cap_rights_init(&rights, CAP_FSTAT, CAP_WRITE);
	if (argc > 1)
		ofp = file(argv[1], "w");
	else
		cap_rights_set(&rights, CAP_IOCTL);
	if (caph_rights_limit(fileno(ofp), &rights) < 0) {
		err(1, "unable to limit rights for %s",
		    argc > 1 ? argv[1] : "stdout");
	}
	if (cap_rights_is_set(&rights, CAP_IOCTL)) {
		unsigned long cmd;

		cmd = TIOCGETA; /* required by isatty(3) in printf(3) */

		if (caph_ioctls_limit(fileno(ofp), &cmd, 1) < 0) {
			err(1, "unable to limit ioctls for %s",
			    argc > 1 ? argv[1] : "stdout");
		}
	}

	caph_cache_catpages();
	if (caph_enter() < 0)
		err(1, "unable to enter capability mode");

	prevbuflen = thisbuflen = 0;
	prevline = thisline = NULL;

	if (getline(&prevline, &prevbuflen, ifp) < 0) {
		if (ferror(ifp))
			err(1, "%s", ifn);
		exit(0);
	}
	tprev = convert(prevline);

	tthis = NULL;
	while (getline(&thisline, &thisbuflen, ifp) >= 0) {
		if (tthis != NULL)
			free(tthis);
		tthis = convert(thisline);

		if (tthis == NULL && tprev == NULL)
			comp = inlcmp(thisline, prevline);
		else if (tthis == NULL || tprev == NULL)
			comp = 1;
		else
			comp = wcscoll(tthis, tprev);

		if (comp) {
			/* If different, print; set previous to new value. */
			show(ofp, prevline);
			p = prevline;
			b1 = prevbuflen;
			prevline = thisline;
			prevbuflen = thisbuflen;
			if (tprev != NULL)
				free(tprev);
			tprev = tthis;
			thisline = p;
			thisbuflen = b1;
			tthis = NULL;
			repeats = 0;
		} else
			++repeats;
	}
	if (ferror(ifp))
		err(1, "%s", ifn);
	show(ofp, prevline);
	exit(0);
}