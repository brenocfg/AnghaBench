#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostent {scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_3__ {scalar_t__ class; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  L2CAP_LM_MASTER ; 
 scalar_t__ L2CAP_PSM_BNEP ; 
 int /*<<< orphan*/  L2CAP_PSM_INVALID (unsigned long) ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int LOG_NDELAY ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 scalar_t__ SDP_SERVICE_CLASS_PANU ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 unsigned long __arraycount (TYPE_1__*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 scalar_t__ bdaddr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdaddr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_aton (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_devaddr (char*,int /*<<< orphan*/ *) ; 
 struct hostent* bt_gethostbyname (char*) ; 
 int /*<<< orphan*/  channel_init () ; 
 int /*<<< orphan*/  client_init () ; 
 char* control_path ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getprogname () ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hstrerror (int /*<<< orphan*/ ) ; 
 char* interface_name ; 
 int /*<<< orphan*/  l2cap_mode ; 
 scalar_t__ l2cap_psm ; 
 int /*<<< orphan*/  local_bdaddr ; 
 int /*<<< orphan*/  main_detach () ; 
 int /*<<< orphan*/  main_exit ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  remote_bdaddr ; 
 int /*<<< orphan*/  server_init () ; 
 int server_limit ; 
 scalar_t__ service_class ; 
 int /*<<< orphan*/ * service_name ; 
 TYPE_1__* services ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  tap_init () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  wait (int*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	unsigned long	ul;
	char *		ep;
	int		ch, status;

	while ((ch = getopt(argc, argv, "a:c:d:i:l:m:p:S:s:")) != -1) {
		switch (ch) {
		case 'a': /* remote address */
			if (!bt_aton(optarg, &remote_bdaddr)) {
				struct hostent  *he;

				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(EXIT_FAILURE, "%s: %s",
					    optarg, hstrerror(h_errno));

				bdaddr_copy(&remote_bdaddr,
					(bdaddr_t *)he->h_addr);
			}

			break;

		case 'c': /* control socket path */
			control_path = optarg;
			break;

		case 'd': /* local address */
			if (!bt_devaddr(optarg, &local_bdaddr)) {
				struct hostent  *he;

				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(EXIT_FAILURE, "%s: %s",
					    optarg, hstrerror(h_errno));

				bdaddr_copy(&local_bdaddr,
					(bdaddr_t *)he->h_addr);
			}
			break;

		case 'i': /* tap interface name */
			if (strchr(optarg, '/') == NULL) {
				asprintf(&ep, "/dev/%s", optarg);
				interface_name = ep;
			} else
				interface_name = optarg;
			break;

		case 'l': /* limit server sessions */
			ul = strtoul(optarg, &ep, 10);
			if (*optarg == '\0' || *ep != '\0' || ul == 0)
				errx(EXIT_FAILURE, "%s: invalid session limit",
					optarg);

			server_limit = ul;
			break;

		case 'm': /* link mode */
			warnx("Setting link mode is not yet supported");
			break;

		case 'p': /* protocol/service multiplexer */
			ul = strtoul(optarg, &ep, 0);
			if (*optarg == '\0' || *ep != '\0'
			    || ul > 0xffff || L2CAP_PSM_INVALID(ul))
				errx(EXIT_FAILURE, "%s: invalid PSM", optarg);

			l2cap_psm = ul;
			break;

		case 's': /* service */
		case 'S': /* service (no SDP) */
			for (ul = 0; strcasecmp(optarg, services[ul].name); ul++) {
				if (ul == __arraycount(services))
					errx(EXIT_FAILURE, "%s: unknown service", optarg);
			}

			if (ch == 's')
				service_name = services[ul].name;

			service_class = services[ul].class;
			break;

		default:
			usage();
			/* NOTREACHED */
		}
	}

	argc -= optind;
	argv += optind;

	/* validate options */
	if (bdaddr_any(&local_bdaddr) || service_class == 0)
		usage();

	if (!bdaddr_any(&remote_bdaddr) && (server_limit != 0 ||
	    control_path != NULL || (service_name != NULL && l2cap_psm != 0)))
		usage();

	/* default options */
	if (interface_name == NULL)
		interface_name = "/dev/tap";

	if (l2cap_psm == 0)
		l2cap_psm = L2CAP_PSM_BNEP;

	if (bdaddr_any(&remote_bdaddr) && server_limit == 0) {
		if (service_class == SDP_SERVICE_CLASS_PANU)
			server_limit = 1;
		else
			server_limit = 7;
	}

#ifdef L2CAP_LM_MASTER
	if (server_limit > 1 && service_class != SDP_SERVICE_CLASS_PANU)
		l2cap_mode |= L2CAP_LM_MASTER;
#endif

	/*
	 * fork() now so that the setup can be done in the child process
	 * (as kqueue is not inherited) but block in the parent until the
	 * setup is finished so we can return an error if necessary.
	 */
	switch(fork()) {
	case -1: /* bad */
		err(EXIT_FAILURE, "fork() failed");

	case 0:	/* child */
		signal(SIGPIPE, SIG_IGN);

		openlog(getprogname(), LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_DAEMON);

		channel_init();
		server_init();
		event_init();
		client_init();
		tap_init();

		main_detach();

		event_dispatch();
		break;

	default: /* parent */
		signal(SIGUSR1, main_exit);
		wait(&status);

		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));

		break;
	}

	err(EXIT_FAILURE, "exiting");
}