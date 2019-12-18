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
struct trussinfo {int strsize; int flags; int /*<<< orphan*/ * outfile; int /*<<< orphan*/  start_time; int /*<<< orphan*/  proclist; int /*<<< orphan*/ * curthread; } ;
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/ * abi; } ;

/* Variables and functions */
 int ABSOLUTETIMESTAMPS ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int COUNTONLY ; 
 int DISPLAYTIDS ; 
 int EXECVEARGS ; 
 int EXECVEENVS ; 
 int FOLLOWFORKS ; 
 int /*<<< orphan*/  INT_MAX ; 
 TYPE_1__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int NOSIGS ; 
 int /*<<< orphan*/  PT_DETACH ; 
 int /*<<< orphan*/  PT_SYSCALL ; 
 int RELATIVETIMESTAMPS ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ atoi (char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  eventloop (struct trussinfo*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  init_syscalls () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_summary (struct trussinfo*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_proc ; 
 int /*<<< orphan*/  setup_and_wait (struct trussinfo*,char**) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_tracing (struct trussinfo*,scalar_t__) ; 
 int /*<<< orphan*/ * stderr ; 
 int strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int ac, char **av)
{
	struct sigaction sa;
	struct trussinfo *trussinfo;
	char *fname;
	char **command;
	const char *errstr;
	pid_t pid;
	int c;

	fname = NULL;

	/* Initialize the trussinfo struct */
	trussinfo = (struct trussinfo *)calloc(1, sizeof(struct trussinfo));
	if (trussinfo == NULL)
		errx(1, "calloc() failed");

	pid = 0;
	trussinfo->outfile = stderr;
	trussinfo->strsize = 32;
	trussinfo->curthread = NULL;
	LIST_INIT(&trussinfo->proclist);
	init_syscalls();
	while ((c = getopt(ac, av, "p:o:facedDs:SH")) != -1) {
		switch (c) {
		case 'p':	/* specified pid */
			pid = atoi(optarg);
			/* make sure i don't trace me */
			if (pid == getpid()) {
				errx(2, "attempt to grab self.");
			}
			break;
		case 'f': /* Follow fork()'s */
			trussinfo->flags |= FOLLOWFORKS;
			break;
		case 'a': /* Print execve() argument strings. */
			trussinfo->flags |= EXECVEARGS;
			break;
		case 'c': /* Count number of system calls and time. */
			trussinfo->flags |= (COUNTONLY | NOSIGS);
			break;
		case 'e': /* Print execve() environment strings. */
			trussinfo->flags |= EXECVEENVS;
			break;
		case 'd': /* Absolute timestamps */
			trussinfo->flags |= ABSOLUTETIMESTAMPS;
			break;
		case 'D': /* Relative timestamps */
			trussinfo->flags |= RELATIVETIMESTAMPS;
			break;
		case 'o':	/* Specified output file */
			fname = optarg;
			break;
		case 's':	/* Specified string size */
			trussinfo->strsize = strtonum(optarg, 0, INT_MAX, &errstr);
			if (errstr)
				errx(1, "maximum string size is %s: %s", errstr, optarg);
			break;
		case 'S':	/* Don't trace signals */
			trussinfo->flags |= NOSIGS;
			break;
		case 'H':
			trussinfo->flags |= DISPLAYTIDS;
			break;
		default:
			usage();
		}
	}

	ac -= optind; av += optind;
	if ((pid == 0 && ac == 0) ||
	    (pid != 0 && ac != 0))
		usage();

	if (fname != NULL) { /* Use output file */
		/*
		 * Set close-on-exec ('e'), so that the output file is not
		 * shared with the traced process.
		 */
		if ((trussinfo->outfile = fopen(fname, "we")) == NULL)
			err(1, "cannot open %s", fname);
	}

	/*
	 * If truss starts the process itself, it will ignore some signals --
	 * they should be passed off to the process, which may or may not
	 * exit.  If, however, we are examining an already-running process,
	 * then we restore the event mask on these same signals.
	 */
	if (pid == 0) {
		/* Start a command ourselves */
		command = av;
		setup_and_wait(trussinfo, command);
		signal(SIGINT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	} else {
		sa.sa_handler = restore_proc;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGTERM, &sa, NULL);
		start_tracing(trussinfo, pid);
	}

	/*
	 * At this point, if we started the process, it is stopped waiting to
	 * be woken up, either in exit() or in execve().
	 */
	if (LIST_FIRST(&trussinfo->proclist)->abi == NULL) {
		/*
		 * If we are not able to handle this ABI, detach from the
		 * process and exit.  If we just created a new process to
		 * run a command, kill the new process rather than letting
		 * it run untraced.
		 */
		if (pid == 0)
			kill(LIST_FIRST(&trussinfo->proclist)->pid, SIGKILL);
		ptrace(PT_DETACH, LIST_FIRST(&trussinfo->proclist)->pid, NULL,
		    0);
		return (1);
	}
	ptrace(PT_SYSCALL, LIST_FIRST(&trussinfo->proclist)->pid, (caddr_t)1,
	    0);

	/*
	 * At this point, it's a simple loop, waiting for the process to
	 * stop, finding out why, printing out why, and then continuing it.
	 * All of the grunt work is done in the support routines.
	 */
	clock_gettime(CLOCK_REALTIME, &trussinfo->start_time);

	eventloop(trussinfo);

	if (trussinfo->flags & COUNTONLY)
		print_summary(trussinfo);

	fflush(trussinfo->outfile);

	return (0);
}