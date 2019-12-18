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
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/  D_MD_ORDER ; 
 int /*<<< orphan*/  HOST_TYPE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_TIME ; 
 int /*<<< orphan*/  REBOOT_TYPE ; 
 int /*<<< orphan*/  TTY_TYPE ; 
 int /*<<< orphan*/  USER_TYPE ; 
 int /*<<< orphan*/  UTXDB_LOG ; 
 int /*<<< orphan*/  addarg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int atol (char*) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 int /*<<< orphan*/  caph_cache_tzdata () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 int d_first ; 
 scalar_t__ dateconv (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 char* file ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hostconv (char*) ; 
 int maxrec ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int noctfix ; 
 char* optarg ; 
 size_t optind ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setutxdb (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sflag ; 
 scalar_t__ snaptime ; 
 int /*<<< orphan*/  stdout ; 
 char* strchr (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtol (char*,char**,int) ; 
 char* ttyconv (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int width ; 
 int /*<<< orphan*/  wtmp () ; 
 int /*<<< orphan*/  xo_err (int,char*,...) ; 
 int /*<<< orphan*/  xo_errx (int,char*,char*) ; 
 int /*<<< orphan*/  xo_finish_atexit ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  yflag ; 

int
main(int argc, char *argv[])
{
	int ch;
	char *p;

	(void) setlocale(LC_TIME, "");
	d_first = (*nl_langinfo(D_MD_ORDER) == 'd');

	(void) setlocale(LC_CTYPE, "");
	p = nl_langinfo(CODESET);
	if (strcmp(p, "UTF-8") == 0 || strcmp(p, "US-ASCII") == 0)
		noctfix = 1;

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);
	atexit(xo_finish_atexit);

	maxrec = -1;
	snaptime = 0;
	while ((ch = getopt(argc, argv, "0123456789d:f:h:n:st:wy")) != -1)
		switch (ch) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			/*
			 * kludge: last was originally designed to take
			 * a number after a dash.
			 */
			if (maxrec == -1) {
				p = strchr(argv[optind - 1], ch);
				if (p == NULL)
					p = strchr(argv[optind], ch);
				maxrec = atol(p);
				if (!maxrec)
					exit(0);
			}
			break;
		case 'd':
			snaptime = dateconv(optarg);
			break;
		case 'f':
			file = optarg;
			break;
		case 'h':
			hostconv(optarg);
			addarg(HOST_TYPE, optarg);
			break;
		case 'n':
			errno = 0;
			maxrec = strtol(optarg, &p, 10);
			if (p == optarg || *p != '\0' || errno != 0 ||
			    maxrec <= 0)
				xo_errx(1, "%s: bad line count", optarg);
			break;
		case 's':
			sflag++;	/* Show delta as seconds */
			break;
		case 't':
			addarg(TTY_TYPE, ttyconv(optarg));
			break;
		case 'w':
			width = 8;
			break;
		case 'y':
			yflag++;
			break;
		case '?':
		default:
			usage();
		}

	if (caph_limit_stdio() < 0)
		xo_err(1, "can't limit stdio rights");

	caph_cache_catpages();
	caph_cache_tzdata();

	/* Cache UTX database. */
	if (setutxdb(UTXDB_LOG, file) != 0)
		xo_err(1, "%s", file != NULL ? file : "(default utx db)");

	if (caph_enter() < 0)
		xo_err(1, "cap_enter");

	if (sflag && width == 8) usage();

	if (argc) {
		setlinebuf(stdout);
		for (argv += optind; *argv; ++argv) {
			if (strcmp(*argv, "reboot") == 0)
				addarg(REBOOT_TYPE, *argv);
#define	COMPATIBILITY
#ifdef	COMPATIBILITY
			/* code to allow "last p5" to work */
			addarg(TTY_TYPE, ttyconv(*argv));
#endif
			addarg(USER_TYPE, *argv);
		}
	}
	wtmp();
	exit(0);
}