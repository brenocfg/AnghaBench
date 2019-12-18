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
typedef  scalar_t__ u_int ;
struct utmpx {int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_type; } ;
struct passwd {char* pw_name; } ;

/* Variables and functions */
 int EPERM ; 
 int ESRCH ; 
 int LOG_AUTH ; 
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int RB_DUMP ; 
 int RB_HALT ; 
 int RB_NOSYNC ; 
 int RB_POWERCYCLE ; 
 int RB_POWEROFF ; 
 int RB_REROOT ; 
 int /*<<< orphan*/  SHUTDOWN_TIME ; 
 int /*<<< orphan*/  SIGEMT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  close (int) ; 
 int dohalt ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_pageins () ; 
 scalar_t__ geteuid () ; 
 char* getlogin () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getprogname () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getuid () ; 
 int kill (int,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pututxline (struct utmpx*) ; 
 int /*<<< orphan*/  reboot (int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write (int,char const*,int) ; 

int
main(int argc, char *argv[])
{
	struct utmpx utx;
	const struct passwd *pw;
	int ch, howto, i, fd, lflag, nflag, qflag, sverrno, Nflag;
	u_int pageins;
	const char *user, *kernel = NULL;

	if (strstr(getprogname(), "halt") != NULL) {
		dohalt = 1;
		howto = RB_HALT;
	} else
		howto = 0;
	lflag = nflag = qflag = Nflag = 0;
	while ((ch = getopt(argc, argv, "cdk:lNnpqr")) != -1)
		switch(ch) {
		case 'c':
			howto |= RB_POWERCYCLE;
			break;
		case 'd':
			howto |= RB_DUMP;
			break;
		case 'k':
			kernel = optarg;
			break;
		case 'l':
			lflag = 1;
			break;
		case 'n':
			nflag = 1;
			howto |= RB_NOSYNC;
			break;
		case 'N':
			nflag = 1;
			Nflag = 1;
			break;
		case 'p':
			howto |= RB_POWEROFF;
			break;
		case 'q':
			qflag = 1;
			break;
		case 'r':
			howto |= RB_REROOT;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
	if (argc != 0)
		usage();

	if ((howto & (RB_DUMP | RB_HALT)) == (RB_DUMP | RB_HALT))
		errx(1, "cannot dump (-d) when halting; must reboot instead");
	if (Nflag && (howto & RB_NOSYNC) != 0)
		errx(1, "-N cannot be used with -n");
	if ((howto & RB_POWEROFF) && (howto & RB_POWERCYCLE))
		errx(1, "-c and -p cannot be used together");
	if ((howto & RB_REROOT) != 0 && howto != RB_REROOT)
		errx(1, "-r cannot be used with -c, -d, -n, or -p");
	if (geteuid()) {
		errno = EPERM;
		err(1, NULL);
	}

	if (qflag) {
		reboot(howto);
		err(1, NULL);
	}

	if (kernel != NULL) {
		fd = open("/boot/nextboot.conf", O_WRONLY | O_CREAT | O_TRUNC,
		    0444);
		if (fd > -1) {
			(void)write(fd, "nextboot_enable=\"YES\"\n", 22);
			(void)write(fd, "kernel=\"", 8L);
			(void)write(fd, kernel, strlen(kernel));
			(void)write(fd, "\"\n", 2);
			close(fd);
		}
	}

	/* Log the reboot. */
	if (!lflag)  {
		if ((user = getlogin()) == NULL)
			user = (pw = getpwuid(getuid())) ?
			    pw->pw_name : "???";
		if (dohalt) {
			openlog("halt", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "halted by %s", user);
		} else if (howto & RB_REROOT) {
			openlog("reroot", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "rerooted by %s", user);
		} else if (howto & RB_POWEROFF) {
			openlog("reboot", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "powered off by %s", user);
		} else if (howto & RB_POWERCYCLE) {
			openlog("reboot", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "power cycled by %s", user);
		} else {
			openlog("reboot", 0, LOG_AUTH | LOG_CONS);
			syslog(LOG_CRIT, "rebooted by %s", user);
		}
	}
	utx.ut_type = SHUTDOWN_TIME;
	gettimeofday(&utx.ut_tv, NULL);
	pututxline(&utx);

	/*
	 * Do a sync early on, so disks start transfers while we're off
	 * killing processes.  Don't worry about writes done before the
	 * processes die, the reboot system call syncs the disks.
	 */
	if (!nflag)
		sync();

	/*
	 * Ignore signals that we can get as a result of killing
	 * parents, group leaders, etc.
	 */
	(void)signal(SIGHUP,  SIG_IGN);
	(void)signal(SIGINT,  SIG_IGN);
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGTERM, SIG_IGN);
	(void)signal(SIGTSTP, SIG_IGN);

	/*
	 * If we're running in a pipeline, we don't want to die
	 * after killing whatever we're writing to.
	 */
	(void)signal(SIGPIPE, SIG_IGN);

	/*
	 * Only init(8) can perform rerooting.
	 */
	if (howto & RB_REROOT) {
		if (kill(1, SIGEMT) == -1)
			err(1, "SIGEMT init");

		return (0);
	}

	/* Just stop init -- if we fail, we'll restart it. */
	if (kill(1, SIGTSTP) == -1)
		err(1, "SIGTSTP init");

	/* Send a SIGTERM first, a chance to save the buffers. */
	if (kill(-1, SIGTERM) == -1 && errno != ESRCH)
		err(1, "SIGTERM processes");

	/*
	 * After the processes receive the signal, start the rest of the
	 * buffers on their way.  Wait 5 seconds between the SIGTERM and
	 * the SIGKILL to give everybody a chance. If there is a lot of
	 * paging activity then wait longer, up to a maximum of approx
	 * 60 seconds.
	 */
	sleep(2);
	for (i = 0; i < 20; i++) {
		pageins = get_pageins();
		if (!nflag)
			sync();
		sleep(3);
		if (get_pageins() == pageins)
			break;
	}

	for (i = 1;; ++i) {
		if (kill(-1, SIGKILL) == -1) {
			if (errno == ESRCH)
				break;
			goto restart;
		}
		if (i > 5) {
			(void)fprintf(stderr,
			    "WARNING: some process(es) wouldn't die\n");
			break;
		}
		(void)sleep(2 * i);
	}

	reboot(howto);
	/* FALLTHROUGH */

restart:
	sverrno = errno;
	errx(1, "%s%s", kill(1, SIGHUP) == -1 ? "(can't restart init): " : "",
	    strerror(sverrno));
	/* NOTREACHED */
}