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
struct rlimit {int rlim_cur; int rlim_max; } ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;
struct netconfig {int nc_flag; int /*<<< orphan*/  nc_protofmly; } ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int /*<<< orphan*/  LOG_CONS ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NC_VISIBLE ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  RPCBINDDLOCK ; 
 int RPC_MAXDATASIZE ; 
 int /*<<< orphan*/  RPC_SVC_CONNMAXREC_SET ; 
 int /*<<< orphan*/  RUN_AS ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ debugging ; 
 scalar_t__ doabort ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int flock (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ geteuid () ; 
 struct netconfig* getnetconfig (void*) ; 
 struct netconfig* getnetconfigent (char*) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  init_transport (struct netconfig*) ; 
 int ipv6_only ; 
 int /*<<< orphan*/  my_svc_run () ; 
 int /*<<< orphan*/  network_init () ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseargs (int,char**) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_warmstart () ; 
 int /*<<< orphan*/  reap ; 
 int /*<<< orphan*/  rpc_control (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rpcbind_abort () ; 
 int rpcbindlockfd ; 
 scalar_t__ runasdaemon ; 
 void* setnetconfig () ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 char* tcptrans ; 
 int /*<<< orphan*/  terminate ; 
 int terminate_rfd ; 
 int terminate_wfd ; 
 char* udptrans ; 
 int /*<<< orphan*/  update_bound_sa () ; 
 scalar_t__ warmstart ; 

int
main(int argc, char *argv[])
{
	struct netconfig *nconf;
	void *nc_handle;	/* Net config handle */
	struct rlimit rl;
	int maxrec = RPC_MAXDATASIZE;
	int error, fds[2];

	parseargs(argc, argv);

	update_bound_sa();

	/* Check that another rpcbind isn't already running. */
	if ((rpcbindlockfd = (open(RPCBINDDLOCK,
	    O_RDONLY|O_CREAT, 0444))) == -1)
		err(1, "%s", RPCBINDDLOCK);

	if(flock(rpcbindlockfd, LOCK_EX|LOCK_NB) == -1 && errno == EWOULDBLOCK)
		errx(1, "another rpcbind is already running. Aborting");

	getrlimit(RLIMIT_NOFILE, &rl);
	if (rl.rlim_cur < 128) {
		if (rl.rlim_max <= 128)
			rl.rlim_cur = rl.rlim_max;
		else
			rl.rlim_cur = 128;
		setrlimit(RLIMIT_NOFILE, &rl);
	}
	openlog("rpcbind", LOG_CONS, LOG_DAEMON);
	if (geteuid()) { /* This command allowed only to root */
		fprintf(stderr, "Sorry. You are not superuser\n");
		exit(1);
	}
	nc_handle = setnetconfig(); 	/* open netconfig file */
	if (nc_handle == NULL) {
		syslog(LOG_ERR, "could not read /etc/netconfig");
		exit(1);
	}
#ifdef PORTMAP
	udptrans = "";
	tcptrans = "";
#endif

	nconf = getnetconfigent("local");
	if (nconf == NULL)
		nconf = getnetconfigent("unix");
	if (nconf == NULL) {
		syslog(LOG_ERR, "%s: can't find local transport\n", argv[0]);
		exit(1);
	}

	rpc_control(RPC_SVC_CONNMAXREC_SET, &maxrec);

	init_transport(nconf);

	while ((nconf = getnetconfig(nc_handle))) {
	    if (nconf->nc_flag & NC_VISIBLE) {
	    	if (ipv6_only == 1 && strcmp(nconf->nc_protofmly,
		    "inet") == 0) {
		    /* DO NOTHING */
		} else
		    init_transport(nconf);
	    }
	}
	endnetconfig(nc_handle);

	/*
	 * Allocate pipe fd to wake main thread from signal handler in non-racy
	 * way.
	 */
	error = pipe(fds);
	if (error != 0)
		err(1, "pipe failed");
	terminate_rfd = fds[0];
	terminate_wfd = fds[1];

	/* catch the usual termination signals for graceful exit */
	(void) signal(SIGCHLD, reap);
	(void) signal(SIGINT, terminate);
	(void) signal(SIGTERM, terminate);
	(void) signal(SIGQUIT, terminate);
	/* ignore others that could get sent */
	(void) signal(SIGPIPE, SIG_IGN);
	(void) signal(SIGHUP, SIG_IGN);
	(void) signal(SIGUSR1, SIG_IGN);
	(void) signal(SIGUSR2, SIG_IGN);
#ifdef WARMSTART
	if (warmstart) {
		read_warmstart();
	}
#endif
	if (debugging) {
		printf("rpcbind debugging enabled.");
		if (doabort) {
			printf("  Will abort on errors!\n");
		} else {
			printf("\n");
		}
	} else {
		if (daemon(0, 0))
			err(1, "fork failed");
	}

	if (runasdaemon) {
		struct passwd *p;

		if((p = getpwnam(RUN_AS)) == NULL) {
			syslog(LOG_ERR, "cannot get uid of daemon: %m");
			exit(1);
		}
		if (setuid(p->pw_uid) == -1) {
			syslog(LOG_ERR, "setuid to daemon failed: %m");
			exit(1);
		}
	}

	network_init();

	my_svc_run();
	syslog(LOG_ERR, "svc_run returned unexpectedly");
	rpcbind_abort();
	/* NOTREACHED */

	return 0;
}