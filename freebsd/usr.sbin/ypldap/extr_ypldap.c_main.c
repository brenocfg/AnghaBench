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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; } ;
struct event {int dummy; } ;
struct env {TYPE_2__* sc_iev; int /*<<< orphan*/  sc_group_gids; int /*<<< orphan*/  sc_user_uids; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  ev; int /*<<< orphan*/  handler; int /*<<< orphan*/  events; TYPE_1__ ibuf; struct env* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  PROC_MAIN ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int SOCK_NONBLOCK ; 
 int SOCK_STREAM ; 
 int YPLDAP_OPT_NOACTION ; 
 int YPLDAP_OPT_VERBOSE ; 
 int /*<<< orphan*/  YPLDAP_USER ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  client_pid ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdline_symset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conffile ; 
 int daemon (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct env*) ; 
 int /*<<< orphan*/  evtimer_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_set (struct event*,int /*<<< orphan*/ ,struct env*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ geteuid () ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imsg_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldapclient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*,char*) ; 
 int /*<<< orphan*/  log_init (int) ; 
 int /*<<< orphan*/  log_warnx (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_dispatch_client ; 
 int /*<<< orphan*/  main_init_timer ; 
 int /*<<< orphan*/  main_shutdown () ; 
 int /*<<< orphan*/  main_sig_handler ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int opts ; 
 scalar_t__ parse_config (struct env*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pipe_main2client ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 scalar_t__ setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct env*) ; 
 int socketpair (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  yp_enable_events () ; 
 int /*<<< orphan*/  yp_init (struct env*) ; 
 int /*<<< orphan*/  ypldap_process ; 

int
main(int argc, char *argv[])
{
	int		 c;
	int		 debug;
	struct passwd	*pw;
	struct env	 env;
	struct event	 ev_sigint;
	struct event	 ev_sigterm;
	struct event	 ev_sigchld;
	struct event	 ev_sighup;
	struct event	 ev_timer;
	struct timeval	 tv;

	debug = 0;
	ypldap_process = PROC_MAIN;

	log_init(1);

	while ((c = getopt(argc, argv, "dD:nf:v")) != -1) {
		switch (c) {
		case 'd':
			debug = 2;
			break;
		case 'D':
			if (cmdline_symset(optarg) < 0)
				log_warnx("could not parse macro definition %s",
				    optarg);
			break;
		case 'n':
			debug = 2;
			opts |= YPLDAP_OPT_NOACTION;
			break;
		case 'f':
			conffile = optarg;
			break;
		case 'v':
			opts |= YPLDAP_OPT_VERBOSE;
			break;
		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (argc)
		usage();

	RB_INIT(&env.sc_user_uids);
	RB_INIT(&env.sc_group_gids);

	if (parse_config(&env, conffile, opts))
		exit(1);
	if (opts & YPLDAP_OPT_NOACTION) {
		fprintf(stderr, "configuration OK\n");
		exit(0);
	}

	if (geteuid())
		errx(1, "need root privileges");

	log_init(debug);

	if (!debug) {
		if (daemon(1, 0) == -1)
			err(1, "failed to daemonize");
	}

	log_info("startup%s", (debug > 1)?" [debug mode]":"");

	if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, PF_UNSPEC,
	    pipe_main2client) == -1)
		fatal("socketpair");

	client_pid = ldapclient(pipe_main2client);

	setproctitle("parent");
	event_init();

	signal_set(&ev_sigint, SIGINT, main_sig_handler, &env);
	signal_set(&ev_sigterm, SIGTERM, main_sig_handler, &env);
	signal_set(&ev_sighup, SIGHUP, main_sig_handler, &env);
	signal_set(&ev_sigchld, SIGCHLD, main_sig_handler, &env);
	signal_add(&ev_sigint, NULL);
	signal_add(&ev_sigterm, NULL);
	signal_add(&ev_sighup, NULL);
	signal_add(&ev_sigchld, NULL);

	close(pipe_main2client[1]);
	if ((env.sc_iev = calloc(1, sizeof(*env.sc_iev))) == NULL)
		fatal(NULL);
	imsg_init(&env.sc_iev->ibuf, pipe_main2client[0]);
	env.sc_iev->handler = main_dispatch_client;

	env.sc_iev->events = EV_READ;
	env.sc_iev->data = &env;
	event_set(&env.sc_iev->ev, env.sc_iev->ibuf.fd, env.sc_iev->events,
	     env.sc_iev->handler, &env);
	event_add(&env.sc_iev->ev, NULL);

	yp_init(&env);

	if ((pw = getpwnam(YPLDAP_USER)) == NULL)
		fatal("getpwnam");

#ifndef DEBUG
	if (setgroups(1, &pw->pw_gid) ||
	    setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) ||
	    setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid))
		fatal("cannot drop privileges");
#else
#warning disabling privilege revocation in debug mode
#endif

	memset(&tv, 0, sizeof(tv));
	evtimer_set(&ev_timer, main_init_timer, &env);
	evtimer_add(&ev_timer, &tv);

	yp_enable_events();
	event_dispatch();
	main_shutdown();

	return (0);
}