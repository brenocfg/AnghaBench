#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCAL ; 
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/  DELIMITERS ; 
 int EOF ; 
 scalar_t__ FREQUENCY ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  GETOPTOPTS ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 char* SPEAKER ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCMGET ; 
 int /*<<< orphan*/  TIOCMSET ; 
 int TIOCM_RTS ; 
 char* USAGE ; 
 int /*<<< orphan*/  _IONBF ; 
 void* atoi (scalar_t__) ; 
 int cdot_clock ; 
 int cpm ; 
 int /*<<< orphan*/  decode (char*) ; 
 scalar_t__ device ; 
 int dot_clock ; 
 int eflag ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fdecode (int /*<<< orphan*/ ) ; 
 scalar_t__ freq ; 
 int getchar () ; 
 int getopt (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hightab ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iso8859_1tab ; 
 int /*<<< orphan*/  iso8859_7tab ; 
 int /*<<< orphan*/  koi8rtab ; 
 int lflag ; 
 int line ; 
 int /*<<< orphan*/  morse (int) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 TYPE_1__ ntty ; 
 int olflags ; 
 int open (char*,int,...) ; 
 scalar_t__ optarg ; 
 scalar_t__ optind ; 
 TYPE_1__ otty ; 
 int pflag ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int rflag ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sflag ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spkr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 int tcgetattr (int,TYPE_1__*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int wpm ; 

int
main(int argc, char *argv[])
{
	int    ch, lflags;
	char  *p, *codeset;

	while ((ch = getopt(argc, argv, GETOPTOPTS)) != -1)
		switch ((char) ch) {
		case 'c':
			cpm = atoi(optarg);
			break;
		case 'd':
			device = optarg;
			break;
		case 'e':
			eflag = 1;
			setvbuf(stdout, 0, _IONBF, 0);
			break;
		case 'f':
			freq = atoi(optarg);
			break;
		case 'l':
			lflag = 1;
			break;
#ifdef SPEAKER
		case 'p':
			pflag = 1;
			break;
#endif
		case 'r':
			rflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'w':
			wpm = atoi(optarg);
			break;
		case '?':
		default:
			errx(1, USAGE);
		}
	if ((sflag && lflag) || (sflag && rflag) || (lflag && rflag)) {
		errx(1, "morse: only one of -l, -s, and -r allowed\n");
	}
	if ((pflag || device) && (sflag || lflag)) {
		errx(1, "morse: only one of -p, -d and -l, -s allowed\n");
	}
	if (cpm == 0) {
		cpm = wpm;
	}
	if ((pflag || device) && ((wpm < 1) || (wpm > 60) || (cpm < 1) || (cpm > 60))) {
		errx(1, "morse: insane speed\n");
	}
	if ((pflag || device) && (freq == 0)) {
		freq = FREQUENCY;
	}
#ifdef SPEAKER
	if (pflag) {
		if ((spkr = open(SPEAKER, O_WRONLY, 0)) == -1) {
			err(1, SPEAKER);
		}
	} else
#endif
	if (device) {
		if ((line = open(device, O_WRONLY | O_NONBLOCK)) == -1) {
			err(1, "open tty line");
		}
		if (tcgetattr(line, &otty) == -1) {
			err(1, "tcgetattr() failed");
		}
		ntty = otty;
		ntty.c_cflag |= CLOCAL;
		tcsetattr(line, TCSANOW, &ntty);
		lflags = fcntl(line, F_GETFL);
		lflags &= ~O_NONBLOCK;
		fcntl(line, F_SETFL, &lflags);
		ioctl(line, TIOCMGET, &lflags);
		lflags &= ~TIOCM_RTS;
		olflags = lflags;
		ioctl(line, TIOCMSET, &lflags);
		(void)signal(SIGHUP, sighandler);
		(void)signal(SIGINT, sighandler);
		(void)signal(SIGQUIT, sighandler);
		(void)signal(SIGTERM, sighandler);
	}
	if (pflag || device) {
		dot_clock = wpm / 2.4;		/* dots/sec */
		dot_clock = 1 / dot_clock;	/* duration of a dot */
		dot_clock = dot_clock / 2;	/* dot_clock runs at twice */
						/* the dot rate */
		dot_clock = dot_clock * 100;	/* scale for ioctl */

		cdot_clock = cpm / 2.4;		/* dots/sec */
		cdot_clock = 1 / cdot_clock;	/* duration of a dot */
		cdot_clock = cdot_clock / 2;	/* dot_clock runs at twice */
						/* the dot rate */
		cdot_clock = cdot_clock * 100;	/* scale for ioctl */
	}

	argc -= optind;
	argv += optind;

	if (setlocale(LC_CTYPE, "") != NULL &&
	    *(codeset = nl_langinfo(CODESET)) != '\0') {
		if (strcmp(codeset, "KOI8-R") == 0)
			hightab = koi8rtab;
		else if (strcmp(codeset, "ISO8859-1") == 0 ||
			 strcmp(codeset, "ISO8859-15") == 0)
			hightab = iso8859_1tab;
		else if (strcmp(codeset, "ISO8859-7") == 0)
			hightab = iso8859_7tab;
	}

	if (lflag) {
		printf("m");
	}
	if (rflag) {
		if (*argv) {
			do {
				p = strtok(*argv, DELIMITERS);
				if (p == NULL) {
					decode(*argv);
				}
				else {
					while (p) {
						decode(p);
						p = strtok(NULL, DELIMITERS);
					}
				}
			} while (*++argv);
			putchar('\n');
		} else {
			fdecode(stdin);
		}
	}
	else if (*argv) {
		do {
			for (p = *argv; *p; ++p) {
				if (eflag)
					putchar(*p);
				morse(*p);
			}
			if (eflag)
				putchar(' ');
			morse(' ');
		} while (*++argv);
	} else {
		while ((ch = getchar()) != EOF) {
			if (eflag)
				putchar(ch);
			morse(ch);
		}
	}
	if (device)
		tcsetattr(line, TCSANOW, &otty);
	exit(0);
}