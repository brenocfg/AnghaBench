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
typedef  scalar_t__ time_t ;
struct tm {long tm_gmtoff; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  login_cap_t ;
struct TYPE_5__ {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/ * DEBUG ; 
 int /*<<< orphan*/  EPERM ; 
 int EastLongitude ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LOGIN_SETALL ; 
 int LONGITUDE_NOTSET ; 
 scalar_t__ Mktime (void*) ; 
 long SECSPERHOUR ; 
 long SECSPERMINUTE ; 
 int UTCOFFSET_NOTSET ; 
 int UTCOffset ; 
 int atoi (void*) ; 
 int /*<<< orphan*/  cal () ; 
 void* calendarFile ; 
 int chdir (int /*<<< orphan*/ ) ; 
 int debug ; 
 int doall ; 
 int /*<<< orphan*/  dodebug (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dumpdates () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ f_time ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  generatedates (struct tm*,struct tm*) ; 
 int getopt (int,char**,char*) ; 
 TYPE_1__* getpwent () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/ * login_getpwclass (TYPE_1__*) ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * outputEncoding ; 
 TYPE_1__* pw ; 
 scalar_t__ setenv (char*,char*,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  settimes (scalar_t__,int,int,int,struct tm*,struct tm*) ; 
 scalar_t__ setusercontext (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strtod (void*,int /*<<< orphan*/ *) ; 
 int strtol (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  tzset () ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int	f_dayAfter = 0;		/* days after current date */
	int	f_dayBefore = 0;	/* days before current date */
	int	Friday = 5;		/* day before weekend */

	int ch;
	struct tm tp1, tp2;

	(void)setlocale(LC_ALL, "");

	while ((ch = getopt(argc, argv, "-A:aB:D:dF:f:l:t:U:W:?")) != -1)
		switch (ch) {
		case '-':		/* backward contemptible */
		case 'a':
			if (getuid()) {
				errno = EPERM;
				err(1, NULL);
			}
			doall = 1;
			break;

		case 'W': /* we don't need no steenking Fridays */
			Friday = -1;
			/* FALLTHROUGH */

		case 'A': /* days after current date */
			f_dayAfter = atoi(optarg);
			if (f_dayAfter < 0)
				errx(1, "number of days must be positive");
			break;

		case 'B': /* days before current date */
			f_dayBefore = atoi(optarg);
			if (f_dayBefore < 0)
				errx(1, "number of days must be positive");
			break;

		case 'D': /* debug output of sun and moon info */
			DEBUG = optarg;
			break;

		case 'd': /* debug output of current date */
			debug = 1;
			break;

		case 'F': /* Change the time: When does weekend start? */
			Friday = atoi(optarg);
			break;

		case 'f': /* other calendar file */
			calendarFile = optarg;
			break;

		case 'l': /* Change longitudal position */
			EastLongitude = strtol(optarg, NULL, 10);
			break;

		case 't': /* other date, for tests */
			f_time = Mktime(optarg);
			break;

		case 'U': /* Change UTC offset */
			UTCOffset = strtod(optarg, NULL);
			break;

		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc)
		usage();

	/* use current time */
	if (f_time <= 0)
		(void)time(&f_time);

	/* if not set, determine where I could be */
	{
		if (UTCOffset == UTCOFFSET_NOTSET &&
		    EastLongitude == LONGITUDE_NOTSET) {
			/* Calculate on difference between here and UTC */
			time_t t;
			struct tm tm;
			long utcoffset, hh, mm, ss;
			double uo;

			time(&t);
			localtime_r(&t, &tm);
			utcoffset = tm.tm_gmtoff;
			/* seconds -> hh:mm:ss */
			hh = utcoffset / SECSPERHOUR;
			utcoffset %= SECSPERHOUR;
			mm = utcoffset / SECSPERMINUTE;
			utcoffset %= SECSPERMINUTE;
			ss = utcoffset;

			/* hh:mm:ss -> hh.mmss */
			uo = mm + (100.0 * (ss / 60.0));
			uo /=  60.0 / 100.0;
			uo = hh + uo / 100;

			UTCOffset = uo;
			EastLongitude = UTCOffset * 15;
		} else if (UTCOffset == UTCOFFSET_NOTSET) {
			/* Base on information given */
			UTCOffset = EastLongitude / 15;
		} else if (EastLongitude == LONGITUDE_NOTSET) {
			/* Base on information given */
			EastLongitude = UTCOffset * 15;
		}
	}

	settimes(f_time, f_dayBefore, f_dayAfter, Friday, &tp1, &tp2);
	generatedates(&tp1, &tp2);

	/*
	 * FROM now on, we are working in UTC.
	 * This will only affect moon and sun related events anyway.
	 */
	if (setenv("TZ", "UTC", 1) != 0)
		errx(1, "setenv: %s", strerror(errno));
	tzset();

	if (debug)
		dumpdates();

	if (DEBUG != NULL) {
		dodebug(DEBUG);
		exit(0);
	}

	if (doall)
		while ((pw = getpwent()) != NULL) {
			pid_t pid;

			if (chdir(pw->pw_dir) == -1)
				continue;
			pid = fork();
			if (pid < 0)
				err(1, "fork");
			if (pid == 0) {
				login_cap_t *lc;

				lc = login_getpwclass(pw);
				if (setusercontext(lc, pw, pw->pw_uid,
				    LOGIN_SETALL) != 0)
					errx(1, "setusercontext");
				cal();
				exit(0);
			}
		}
	else {
#ifdef WITH_ICONV
		/* Save the information about the encoding used in the terminal. */
		outputEncoding = strdup(nl_langinfo(CODESET));
		if (outputEncoding == NULL)
			errx(1, "cannot allocate memory");
#endif
		cal();
	}
	exit(0);
}