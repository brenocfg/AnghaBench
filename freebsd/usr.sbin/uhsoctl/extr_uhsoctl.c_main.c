#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_5__ {int tv_sec; scalar_t__ tv_usec; } ;
struct itimerval {TYPE_2__ it_value; TYPE_1__ it_interval; } ;
struct ctx {int pdp_ctx; char* pdp_apn; char* pdp_user; char* pdp_pwd; char* pin; int con_net_type; int flags; char* resolv_path; int dbm; int /*<<< orphan*/  pfh; scalar_t__ con_status; scalar_t__ fd; int /*<<< orphan*/  ifnam; int /*<<< orphan*/ * ns; int /*<<< orphan*/ * resolv; scalar_t__ con_net_stat; int /*<<< orphan*/ * con_oper; int /*<<< orphan*/ * con_apn; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {int res; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int FLG_DAEMON ; 
 int FLG_DELAYED ; 
 int FLG_NODAEMON ; 
 int FLG_WDEXP ; 
 int IPASSIGNED ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int MODE_CONN ; 
#define  MODE_DISC 128 
 char* RESOLV_PATH ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int at_async (struct ctx*,struct ctx*) ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  daemonize (struct ctx*) ; 
 int do_connect (struct ctx*,char*) ; 
 int /*<<< orphan*/  do_disconnect (struct ctx*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char** get_tty (struct ctx*) ; 
 int getopt (int,char**,char*) ; 
 char** network_access_type ; 
 size_t optind ; 
 int /*<<< orphan*/  pidfile_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int running ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_disconnect (char const*) ; 
 int setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sig_handle ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ syslog_open ; 
 TYPE_3__ timers ; 
 int /*<<< orphan*/  tmr_add (TYPE_3__*,int,int,int /*<<< orphan*/ *,struct ctx*) ; 
 int /*<<< orphan*/  tmr_watchdog ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  watchdog_disable (struct ctx*) ; 
 int /*<<< orphan*/  watchdog_reset (struct ctx*,int) ; 

int
main(int argc, char *argv[])
{
	int ch, error, mode;
	const char *ifnam = NULL;
	char *tty = NULL;
	char **p, **tty_list;
	fd_set set;
	struct ctx ctx;
	struct itimerval it;

	TAILQ_INIT(&timers.head);
	timers.res = 1;

	ctx.pdp_ctx = 1;
	ctx.pdp_apn = ctx.pdp_user = ctx.pdp_pwd = NULL;
	ctx.pin = NULL;

	ctx.con_status = 0;
	ctx.con_apn = NULL;
	ctx.con_oper = NULL;
	ctx.con_net_stat = 0;
	ctx.con_net_type = -1;
	ctx.flags = 0;
	ctx.resolv_path = RESOLV_PATH;
	ctx.resolv = NULL;
	ctx.ns = NULL;
	ctx.dbm = 0;

	mode = MODE_CONN;
	ctx.flags |= FLG_DELAYED;

	while ((ch = getopt(argc, argv, "?ha:p:c:u:k:r:f:dbn")) != -1) {
		switch (ch) {
		case 'a':
			ctx.pdp_apn = argv[optind - 1];
			break;
		case 'c':
			ctx.pdp_ctx = strtol(argv[optind - 1], NULL, 10);
			if (ctx.pdp_ctx < 1) {
				warnx("Invalid context ID, defaulting to 1");
				ctx.pdp_ctx = 1;
			}
			break;
		case 'p':
			ctx.pin = argv[optind - 1];
			break;
		case 'u':
			ctx.pdp_user = argv[optind - 1];
			break;
		case 'k':
			ctx.pdp_pwd = argv[optind - 1];
			break;
		case 'r':
			ctx.resolv_path = argv[optind - 1];
			break;
		case 'd':
			mode = MODE_DISC;
			break;
		case 'b':
			ctx.flags &= ~FLG_DELAYED;
			break;
		case 'n':
			ctx.flags |= FLG_NODAEMON;
			break;
		case 'f':
			tty = argv[optind - 1];
			break;
		case 'h':
		case '?':
		default:
			usage(argv[0]);
			exit(EXIT_SUCCESS);
		}
	}

	argc -= optind;
	argv += optind;

	if (argc < 1)
		errx(1, "no interface given");

	ifnam = argv[argc - 1];
	ctx.ifnam = strdup(ifnam);

	switch (mode) {
	case MODE_DISC:
		printf("Disconnecting %s\n", ifnam);
		send_disconnect(ifnam);
		exit(EXIT_SUCCESS);
	default:
		break;
	}

	signal(SIGHUP, sig_handle);
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	signal(SIGTERM, sig_handle);
	signal(SIGALRM, sig_handle);

	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;
	it.it_value.tv_sec = 1;
	it.it_value.tv_usec = 0;
	error = setitimer(ITIMER_REAL, &it, NULL);
	if (error != 0)
		errx(1, "setitimer");

	tmr_add(&timers, 1, 5, &tmr_watchdog, &ctx);
	watchdog_reset(&ctx, 15);
	
	if (tty != NULL) {
		error = do_connect(&ctx, tty);
		if (error != 0)
			errx(1, "Failed to open %s", tty);
	}
	else {
		tty_list = get_tty(&ctx);
		if (tty_list == NULL)
			errx(1, "%s does not appear to be a uhso device", ifnam);
#ifdef DEBUG
		if (tty_list == NULL) {
			fprintf(stderr, "get_tty returned empty list\n");
		} else {
			fprintf(stderr, "tty list:\n");
			for (p = tty_list; *p != NULL; p++) {
				fprintf(stderr, "\t %s\n", *p);
			}
		}
#endif
		for (p = tty_list; *p != NULL; p++) {
			error = do_connect(&ctx, *p);
			if (error == 0) {
				tty = *p;
				break;
			}
		}
		if (*p == NULL)
			errx(1, "Failed to obtain a control port, "
			    "try specifying one manually");
	}

	if (!(ctx.flags & FLG_DELAYED) && !(ctx.flags & FLG_NODAEMON))
		daemonize(&ctx);


	FD_ZERO(&set);
	FD_SET(ctx.fd, &set);
	for (;;) {

		watchdog_disable(&ctx);
		error = select(ctx.fd + 1, &set, NULL, NULL, NULL);
		if (error <= 0) {
			if (running && errno == EINTR)
				continue;
			if (ctx.flags & FLG_WDEXP) {
				ctx.flags &= ~FLG_WDEXP;
				watchdog_reset(&ctx, 5);
				do_disconnect(&ctx);
				watchdog_reset(&ctx, 15);
				do_connect(&ctx, tty);
				running = 1;
				continue;
			}

			break;
		}

		if (FD_ISSET(ctx.fd, &set)) {
			watchdog_reset(&ctx, 15);
			error = at_async(&ctx, &ctx);
			if (error != 0)
				break;
		}
		FD_SET(ctx.fd, &set);

		if (!(ctx.flags & FLG_DAEMON) && (ctx.flags & IPASSIGNED)) {
			printf("Status: %s (%s)",
			    ctx.con_status ? "connected" : "disconnected",
			    network_access_type[ctx.con_net_type]);
			if (ctx.dbm < 0)
				printf(", signal: %d dBm", ctx.dbm);
			printf("\t\t\t\r");
			fflush(stdout);
		}
	}
	if (!(ctx.flags & FLG_DAEMON) && (ctx.flags & IPASSIGNED))
		printf("\n");

	signal(SIGHUP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGALRM, SIG_IGN);

	do_disconnect(&ctx);

	if (ctx.flags & FLG_DAEMON) {
		pidfile_remove(ctx.pfh);
		if (syslog_open)
			closelog();
	}

	return (0);
}