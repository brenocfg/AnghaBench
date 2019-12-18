#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct tm {char* tm_zone; } ;
struct passwd {char* pw_name; } ;
struct pam_conv {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_7__ {int tv_sec; } ;
struct itimerval {TYPE_2__ it_value; int /*<<< orphan*/  it_interval; } ;
typedef  int /*<<< orphan*/  s1 ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  pam_handle_t ;
typedef  int /*<<< orphan*/  hostname ;
struct TYPE_6__ {int /*<<< orphan*/  c_lflag; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  ECHO ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  LOG_AUTH ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int MAXHOSTNAMELEN ; 
 int PAM_AUTH_ERR ; 
 int PAM_MAXTRIES ; 
 int PAM_SUCCESS ; 
 int PAM_SYSTEM_ERR ; 
 int PAM_USER_UNKNOWN ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int TCSADRAIN ; 
 int TCSASOFT ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  VT_LOCKSWITCH ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 char* asctime (struct tm*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bye (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  hi (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct tm* localtime (scalar_t__*) ; 
 scalar_t__ nexttime ; 
 int no_timeout ; 
 TYPE_1__ ntty ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openpam_ttyconv ; 
 int /*<<< orphan*/  optarg ; 
 int pam_authenticate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pam_end (int /*<<< orphan*/ *,int) ; 
 int pam_start (char*,char*,struct pam_conv const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pam_strerror (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 scalar_t__ setuid (scalar_t__) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 TYPE_2__ timeout ; 
 TYPE_1__ tty ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int vtyunlock ; 
 int /*<<< orphan*/  zerotime ; 

int
main(int argc, char **argv)
{
	static const struct pam_conv pamc = { &openpam_ttyconv, NULL };
	pam_handle_t *pamh;
	struct passwd *pw;
	struct itimerval ntimer, otimer;
	struct tm *timp;
	time_t timval;
	int ch, failures, pam_err, sectimeout, usemine, vtylock;
	char *ap, *ttynam, *tzn;
	char hostname[MAXHOSTNAMELEN], s[BUFSIZ], s1[BUFSIZ];

	openlog("lock", 0, LOG_AUTH);

	pam_err = PAM_SYSTEM_ERR; /* pacify GCC */

	sectimeout = TIMEOUT;
	pamh = NULL;
	pw = NULL;
	usemine = 0;
	no_timeout = 0;
	vtylock = 0;
	while ((ch = getopt(argc, argv, "npt:v")) != -1)
		switch((char)ch) {
		case 't':
			if ((sectimeout = atoi(optarg)) <= 0)
				errx(1, "illegal timeout value");
			break;
		case 'p':
			usemine = 1;
			if (!(pw = getpwuid(getuid())))
				errx(1, "unknown uid %d", getuid());
			break;
		case 'n':
			no_timeout = 1;
			break;
		case 'v':
			vtylock = 1;
			break;
		case '?':
		default:
			usage();
		}
	timeout.tv_sec = sectimeout * 60;

	if (!usemine) {	/* -p with PAM or S/key needs privs */
		/* discard privs */
		if (setuid(getuid()) != 0)
			errx(1, "setuid failed");
	}

	if (tcgetattr(0, &tty))		/* get information for header */
		exit(1);
	gethostname(hostname, sizeof(hostname));
	if (!(ttynam = ttyname(0)))
		errx(1, "not a terminal?");
	if (strncmp(ttynam, _PATH_DEV, strlen(_PATH_DEV)) == 0)
		ttynam += strlen(_PATH_DEV);
	timval = time(NULL);
	nexttime = timval + (sectimeout * 60);
	timp = localtime(&timval);
	ap = asctime(timp);
	tzn = timp->tm_zone;

	(void)signal(SIGINT, quit);
	(void)signal(SIGQUIT, quit);
	ntty = tty; ntty.c_lflag &= ~ECHO;
	(void)tcsetattr(0, TCSADRAIN|TCSASOFT, &ntty);

	if (usemine) {
		pam_err = pam_start("lock", pw->pw_name, &pamc, &pamh);
		if (pam_err != PAM_SUCCESS)
			err(1, "pam_start: %s", pam_strerror(NULL, pam_err));
	} else {
		/* get key and check again */
		(void)printf("Key: ");
		if (!fgets(s, sizeof(s), stdin) || *s == '\n')
			quit(0);
		(void)printf("\nAgain: ");
		/*
		 * Don't need EOF test here, if we get EOF, then s1 != s
		 * and the right things will happen.
		 */
		(void)fgets(s1, sizeof(s1), stdin);
		(void)putchar('\n');
		if (strcmp(s1, s)) {
			(void)printf("\07lock: passwords didn't match.\n");
			(void)tcsetattr(0, TCSADRAIN|TCSASOFT, &tty);
			exit(1);
		}
		s[0] = '\0';
	}

	/* set signal handlers */
	(void)signal(SIGINT, hi);
	(void)signal(SIGQUIT, hi);
	(void)signal(SIGTSTP, hi);
	(void)signal(SIGALRM, bye);

	ntimer.it_interval = zerotime;
	ntimer.it_value = timeout;
	if (!no_timeout)
		setitimer(ITIMER_REAL, &ntimer, &otimer);
	if (vtylock) {
		/*
		 * If this failed, we want to err out; warn isn't good
		 * enough, since we don't want the user to think that
		 * everything is nice and locked because they got a
		 * "Key:" prompt.
		 */
		if (ioctl(0, VT_LOCKSWITCH, &vtylock) == -1) {
			(void)tcsetattr(0, TCSADRAIN|TCSASOFT, &tty);
			err(1, "locking vty");
		}
		vtyunlock = 0x2;
	}

	/* header info */
	if (pw != NULL)
		(void)printf("lock: %s using %s on %s.", pw->pw_name,
		    ttynam, hostname);
	else
		(void)printf("lock: %s on %s.", ttynam, hostname);
	if (no_timeout)
		(void)printf(" no timeout.");
	else
		(void)printf(" timeout in %d minute%s.", sectimeout,
		    sectimeout != 1 ? "s" : "");
	if (vtylock)
		(void)printf(" vty locked.");
	(void)printf("\ntime now is %.20s%s%s", ap, tzn, ap + 19);

	failures = 0;

	for (;;) {
		if (usemine) {
			pam_err = pam_authenticate(pamh, 0);
			if (pam_err == PAM_SUCCESS)
				break;

			if (pam_err != PAM_AUTH_ERR &&
			    pam_err != PAM_USER_UNKNOWN &&
			    pam_err != PAM_MAXTRIES) {
				syslog(LOG_ERR, "pam_authenticate: %s",
				    pam_strerror(pamh, pam_err));
			}
			
			goto tryagain;
		}
		(void)printf("Key: ");
		if (!fgets(s, sizeof(s), stdin)) {
			clearerr(stdin);
			hi(0);
			goto tryagain;
		}
		if (!strcmp(s, s1))
			break;
		(void)printf("\07\n");
	    	failures++;
		if (getuid() == 0)
	    	    syslog(LOG_NOTICE, "%d ROOT UNLOCK FAILURE%s (%s on %s)",
			failures, failures > 1 ? "S": "", ttynam, hostname);
tryagain:
		if (tcgetattr(0, &ntty) && (errno != EINTR))
			exit(1);
		sleep(1);		/* to discourage guessing */
	}
	if (getuid() == 0)
		syslog(LOG_NOTICE, "ROOT UNLOCK ON hostname %s port %s",
		    hostname, ttynam);
	if (usemine)
		(void)pam_end(pamh, pam_err);
	quit(0);
	return(0); /* not reached */
}