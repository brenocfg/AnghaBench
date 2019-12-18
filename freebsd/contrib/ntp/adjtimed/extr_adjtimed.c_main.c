#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; long tv_usec; } ;
struct sigvec {int /*<<< orphan*/  sv_mask; scalar_t__ sv_flags; int /*<<< orphan*/  sv_handler; } ;
struct msqid_ds {int dummy; } ;
struct TYPE_3__ {int code; int /*<<< orphan*/  mtype; struct timeval tv; } ;
struct TYPE_4__ {TYPE_1__ msgb; int /*<<< orphan*/  msgp; } ;
typedef  TYPE_2__ MsgBuf ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustClockRate (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  CLIENT ; 
 int /*<<< orphan*/  Cleanup () ; 
#define  DELTA1 129 
#define  DELTA2 128 
 scalar_t__ EEXIST ; 
 scalar_t__ EINTR ; 
 char EOF ; 
 int /*<<< orphan*/  Exit (int) ; 
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int InitClockRate () ; 
 int /*<<< orphan*/  KEY ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_LOCAL6 ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  MSGSIZE ; 
 int /*<<< orphan*/  PROCLOCK ; 
 int /*<<< orphan*/  ResetClockRate ; 
 int /*<<< orphan*/  SERVER ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN () ; 
 int /*<<< orphan*/  TIOCNOTTY ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fileno (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mqid ; 
 int msgctl (int,int /*<<< orphan*/ ,struct msqid_ds*) ; 
 int msgget (int /*<<< orphan*/ ,int) ; 
 int msgrcv (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msgsnd (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int nice (int) ; 
 char ntp_getopt (int,char**,char*) ; 
 int open (char*) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ plock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  setpgrp () ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  sigvector (int /*<<< orphan*/ ,struct sigvec*,struct sigvec*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sysdebug ; 
 double tvtod (struct timeval) ; 
 scalar_t__ verbose ; 

int
main(
	int argc,
	char *argv[]
	)
{
	struct timeval remains;
	struct sigvec vec;
	MsgBuf msg;
	char ch;
	int nofork = 0;
	int fd;

	progname = argv[0];

#ifdef LOG_LOCAL6
	openlog("adjtimed", LOG_PID, LOG_LOCAL6);
#else
	openlog("adjtimed", LOG_PID);
#endif

	while ((ch = ntp_getopt(argc, argv, "hkrvdfp:")) != EOF) {
		switch (ch) {
		    case 'k':
		    case 'r':
			if ((mqid = msgget(KEY, 0)) != -1) {
				if (msgctl(mqid, IPC_RMID, (struct msqid_ds *)0) == -1) {
					msyslog(LOG_ERR, "remove old message queue: %m");
					perror("adjtimed: remove old message queue");
					exit(1);
				}
			}

			if (ch == 'k')
			    exit(0);

			break;

		    case 'v':
			++verbose, nofork = 1;
			break;

		    case 'd':
			++sysdebug;
			break;

		    case 'f':
			nofork = 1;
			break;

		    case 'p':
			fputs("adjtimed: -p option ignored\n", stderr);
			break;

		    default:
			puts("usage: adjtimed -hkrvdf");
			puts("-h\thelp");
			puts("-k\tkill existing adjtimed, if any");
			puts("-r\trestart (kills existing adjtimed, if any)");
			puts("-v\tdebug output (repeat for more output)");
			puts("-d\tsyslog output (repeat for more output)");
			puts("-f\tno fork");
			msyslog(LOG_ERR, "usage error");
			exit(1);
		} /* switch */
	} /* while */

	if (!nofork) {
		switch (fork()) {
		    case 0:
			close(fileno(stdin));
			close(fileno(stdout));
			close(fileno(stderr));

#ifdef TIOCNOTTY
			if ((fd = open("/dev/tty")) != -1) {
				ioctl(fd, TIOCNOTTY, 0);
				close(fd);
			}
#else
			setpgrp();
#endif
			break;

		    case -1:
			msyslog(LOG_ERR, "fork: %m");
			perror("adjtimed: fork");
			exit(1);

		    default:
			exit(0);
		} /* switch */
	} /* if */

	if (nofork) {
		setvbuf(stdout, NULL, _IONBF, BUFSIZ);
		setvbuf(stderr, NULL, _IONBF, BUFSIZ);
	}

	msyslog(LOG_INFO, "started");
	if (verbose) printf("adjtimed: started\n");

	if (InitClockRate() == -1)
	    Exit(2);

	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGQUIT, SIG_IGN);
	(void)signal(SIGTERM, Cleanup);

	vec.sv_handler = ResetClockRate;
	vec.sv_flags = 0;
	vec.sv_mask = ~0;
	sigvector(SIGALRM, &vec, (struct sigvec *)0);

	if (msgget(KEY, IPC_CREAT|IPC_EXCL) == -1) {
		if (errno == EEXIST) {
			msyslog(LOG_ERR, "message queue already exists, use -r to remove it");
			fputs("adjtimed: message queue already exists, use -r to remove it\n",
			      stderr);
			Exit(1);
		}

		msyslog(LOG_ERR, "create message queue: %m");
		perror("adjtimed: create message queue");
		Exit(1);
	}

	if ((mqid = msgget(KEY, 0)) == -1) {
		msyslog(LOG_ERR, "get message queue id: %m");
		perror("adjtimed: get message queue id");
		Exit(1);
	}
  
	/* Lock process in memory to improve response time */
	if (plock(PROCLOCK)) {
		msyslog(LOG_ERR, "plock: %m");
		perror("adjtimed: plock");
		Cleanup();
	}

	/* Also raise process priority.
	 * If we do not get run when we want, this leads to bad timekeeping
	 * and "Previous time adjustment didn't complete" gripes from xntpd.
	 */
	if (nice(-10) == -1) {
		msyslog(LOG_ERR, "nice: %m");
		perror("adjtimed: nice");
		Cleanup();
	}

	for (;;) {
		if (msgrcv(mqid, &msg.msgp, MSGSIZE, CLIENT, 0) == -1) {
			if (errno == EINTR) continue;
			msyslog(LOG_ERR, "read message: %m");
			perror("adjtimed: read message");
			Cleanup();
		}

		switch (msg.msgb.code) {
		    case DELTA1:
		    case DELTA2:
			AdjustClockRate(&msg.msgb.tv, &remains);

			if (msg.msgb.code == DELTA2) {
				msg.msgb.tv = remains;
				msg.msgb.mtype = SERVER;

				while (msgsnd(mqid, &msg.msgp, MSGSIZE, 0) == -1) {
					if (errno == EINTR) continue;
					msyslog(LOG_ERR, "send message: %m");
					perror("adjtimed: send message");
					Cleanup();
				}
			}

			if (remains.tv_sec + remains.tv_usec != 0L) {
				if (verbose) {
					printf("adjtimed: previous correction remaining %.6fs\n",
					       tvtod(remains));
				}
				if (sysdebug) {
					msyslog(LOG_INFO, "previous correction remaining %.6fs",
						tvtod(remains));
				}
			}
			break;

		    default:
			fprintf(stderr, "adjtimed: unknown message code %d\n", msg.msgb.code);
			msyslog(LOG_ERR, "unknown message code %d", msg.msgb.code);
		} /* switch */
	} /* loop */
}