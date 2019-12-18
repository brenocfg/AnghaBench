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
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr_rfcomm {int rfcomm_len; int rfcomm_channel; int server_channel; int /*<<< orphan*/  rfcomm_bdaddr; void* rfcomm_family; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; } ;
struct sockaddr {int dummy; } ;
struct sigaction {int rfcomm_len; int rfcomm_channel; int server_channel; int /*<<< orphan*/  rfcomm_bdaddr; void* rfcomm_family; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_handler; } ;
struct hostent {int /*<<< orphan*/ * h_addr; } ;
typedef  int /*<<< orphan*/  sp ;
typedef  struct sockaddr_rfcomm sdp_sp_profile_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  ra ;
typedef  int /*<<< orphan*/  ma ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  bt_addr_any ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 void* AF_BLUETOOTH ; 
 int /*<<< orphan*/  BLUETOOTH_PROTO_RFCOMM ; 
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int LOG_NDELAY ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int /*<<< orphan*/ * NG_HCI_BDADDR_ANY ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SA_NOCLDWAIT ; 
 int SDP_SERVICE_CLASS_DIALUP_NETWORKING ; 
 int SDP_SERVICE_CLASS_FAX ; 
 int SDP_SERVICE_CLASS_LAN_ACCESS_USING_PPP ; 
 int SDP_SERVICE_CLASS_SERIAL_PORT ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int SPPD_BUFFER_SIZE ; 
 int /*<<< orphan*/  SPPD_IDENT ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bt_aton (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hostent* bt_gethostbyname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errc (int,int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hstrerror (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 scalar_t__ max (int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_rfcomm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * optarg ; 
 scalar_t__ rfcomm_channel_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int*) ; 
 int /*<<< orphan*/  sdp_close (void*) ; 
 scalar_t__ sdp_error (void*) ; 
 void* sdp_open_local (int /*<<< orphan*/ *) ; 
 scalar_t__ sdp_register_service (void*,int,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdp_unregister_service (void*,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sockaddr_rfcomm*,int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sppd_read (int,char*,int) ; 
 int /*<<< orphan*/  sppd_sighandler ; 
 scalar_t__ sppd_ttys_open (char**,int*,int*) ; 
 scalar_t__ sppd_write (int,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (scalar_t__) ; 
 int strtoul (int /*<<< orphan*/ *,char**,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tolower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[]) 
{
	struct sigaction	 sa;
	struct sockaddr_rfcomm	 ra;
	bdaddr_t		 addr;
	int			 n, background, channel, service,
				 s, amaster, aslave, fd, doserver,
				 dopty;
	fd_set			 rfd;
	char			*tty = NULL, *ep = NULL, buf[SPPD_BUFFER_SIZE];

	memcpy(&addr, NG_HCI_BDADDR_ANY, sizeof(addr));
	background = channel = 0;
	service = SDP_SERVICE_CLASS_SERIAL_PORT;
	doserver = 0;
	dopty = 0;

	/* Parse command line options */
	while ((n = getopt(argc, argv, "a:bc:thS")) != -1) {
		switch (n) { 
		case 'a': /* BDADDR */
			if (!bt_aton(optarg, &addr)) {
				struct hostent	*he = NULL;

				if ((he = bt_gethostbyname(optarg)) == NULL)
					errx(1, "%s: %s", optarg, hstrerror(h_errno));

				memcpy(&addr, he->h_addr, sizeof(addr));
			}
			break;

		case 'c': /* RFCOMM channel */
			channel = strtoul(optarg, &ep, 10);
			if (*ep != '\0') {
				channel = 0;
				switch (tolower(optarg[0])) {
				case 'd': /* DialUp Networking */
					service = SDP_SERVICE_CLASS_DIALUP_NETWORKING;
					break;

				case 'f': /* Fax */
					service = SDP_SERVICE_CLASS_FAX;
					break;

				case 'l': /* LAN */
					service = SDP_SERVICE_CLASS_LAN_ACCESS_USING_PPP;
					break;

				case 's': /* Serial Port */
					service = SDP_SERVICE_CLASS_SERIAL_PORT;
					break;

				default:
					errx(1, "Unknown service name: %s",
						optarg);
					/* NOT REACHED */
				}
			}
			break;

		case 'b': /* Run in background */
			background = 1;
			break;

		case 't': /* Open pseudo TTY */
			dopty = 1;
			break;

		case 'S':
			doserver = 1;
			break;

		case 'h':
		default:
			usage();
			/* NOT REACHED */
		}
	}

	/* Check if we have everything we need */
	if (!doserver && memcmp(&addr, NG_HCI_BDADDR_ANY, sizeof(addr)) == 0)
		usage();
		/* NOT REACHED */

	/* Set signal handlers */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sppd_sighandler;

	if (sigaction(SIGTERM, &sa, NULL) < 0)
		err(1, "Could not sigaction(SIGTERM)");
 
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err(1, "Could not sigaction(SIGHUP)");
 
	if (sigaction(SIGINT, &sa, NULL) < 0)
		err(1, "Could not sigaction(SIGINT)");

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_NOCLDWAIT;

	if (sigaction(SIGCHLD, &sa, NULL) < 0)
		err(1, "Could not sigaction(SIGCHLD)");

	/* Open TTYs */
	if (dopty) {
		if (sppd_ttys_open(&tty, &amaster, &aslave) < 0)
			exit(1);

		fd = amaster;
	} else {
		if (background)
			usage();

		amaster = STDIN_FILENO;
		fd = STDOUT_FILENO;
	}

	/* Open RFCOMM connection */

	if (doserver) {
		struct sockaddr_rfcomm	 ma;
		bdaddr_t		 bt_addr_any;
		sdp_sp_profile_t	 sp;
		void			*ss;
		uint32_t		 sdp_handle;
		int			 acceptsock, aaddrlen;

		acceptsock = socket(PF_BLUETOOTH, SOCK_STREAM,
					BLUETOOTH_PROTO_RFCOMM);
		if (acceptsock < 0)
			err(1, "Could not create socket");

		memcpy(&bt_addr_any, NG_HCI_BDADDR_ANY, sizeof(bt_addr_any));

		memset(&ma, 0, sizeof(ma));
		ma.rfcomm_len = sizeof(ma);
		ma.rfcomm_family = AF_BLUETOOTH;
		memcpy(&ma.rfcomm_bdaddr, &bt_addr_any, sizeof(bt_addr_any));
		ma.rfcomm_channel = channel;

		if (bind(acceptsock, (struct sockaddr *)&ma, sizeof(ma)) < 0)
			err(1, "Could not bind socket on channel %d", channel);
		if (listen(acceptsock, 10) != 0)
			err(1, "Could not listen on socket");

		aaddrlen = sizeof(ma);
		if (getsockname(acceptsock, (struct sockaddr *)&ma, &aaddrlen) < 0)
			err(1, "Could not get socket name");
		channel = ma.rfcomm_channel;

		ss = sdp_open_local(NULL);
		if (ss == NULL)
			errx(1, "Unable to create local SDP session");
		if (sdp_error(ss) != 0)
			errx(1, "Unable to open local SDP session. %s (%d)",
			    strerror(sdp_error(ss)), sdp_error(ss));
		memset(&sp, 0, sizeof(sp));
		sp.server_channel = channel;

		if (sdp_register_service(ss, SDP_SERVICE_CLASS_SERIAL_PORT,
				&bt_addr_any, (void *)&sp, sizeof(sp),
				&sdp_handle) != 0) {
			errx(1, "Unable to register LAN service with "
			    "local SDP daemon. %s (%d)",
			    strerror(sdp_error(ss)), sdp_error(ss));
		}

		s = -1;
		while (s < 0) {
			aaddrlen = sizeof(ra);
			s = accept(acceptsock, (struct sockaddr *)&ra,
			    &aaddrlen);
			if (s < 0)
				err(1, "Unable to accept()");
			if (memcmp(&addr, NG_HCI_BDADDR_ANY, sizeof(addr)) &&
			    memcmp(&addr, &ra.rfcomm_bdaddr, sizeof(addr))) {
				warnx("Connect from wrong client");
				close(s);
				s = -1;
			}
		}
		sdp_unregister_service(ss, sdp_handle);
		sdp_close(ss);
		close(acceptsock);
	} else {
		/* Check channel, if was not set then obtain it via SDP */
		if (channel == 0 && service != 0)
			if (rfcomm_channel_lookup(NULL, &addr,
				    service, &channel, &n) != 0)
				errc(1, n, "Could not obtain RFCOMM channel");
		if (channel <= 0 || channel > 30)
			errx(1, "Invalid RFCOMM channel number %d", channel);

		s = socket(PF_BLUETOOTH, SOCK_STREAM, BLUETOOTH_PROTO_RFCOMM);
		if (s < 0)
			err(1, "Could not create socket");

		memset(&ra, 0, sizeof(ra));
		ra.rfcomm_len = sizeof(ra);
		ra.rfcomm_family = AF_BLUETOOTH;

		if (bind(s, (struct sockaddr *) &ra, sizeof(ra)) < 0)
			err(1, "Could not bind socket");

		memcpy(&ra.rfcomm_bdaddr, &addr, sizeof(ra.rfcomm_bdaddr));
		ra.rfcomm_channel = channel;

		if (connect(s, (struct sockaddr *) &ra, sizeof(ra)) < 0)
			err(1, "Could not connect socket");
	}

	/* Became daemon if required */
	if (background && daemon(0, 0) < 0)
		err(1, "Could not daemon()");

	openlog(SPPD_IDENT, LOG_NDELAY|LOG_PERROR|LOG_PID, LOG_DAEMON);
	syslog(LOG_INFO, "Starting on %s...", (tty != NULL)? tty : "stdin/stdout");

	/* Print used tty on stdout for wrappers to pick up */
	if (!background)
		fprintf(stdout, "%s\n", tty);

	for (done = 0; !done; ) {
		FD_ZERO(&rfd);
		FD_SET(amaster, &rfd);
		FD_SET(s, &rfd);

		n = select(max(amaster, s) + 1, &rfd, NULL, NULL, NULL);
		if (n < 0) {
			if (errno == EINTR)
				continue;

			syslog(LOG_ERR, "Could not select(). %s",
					strerror(errno));
			exit(1);
		}

		if (n == 0)
			continue;

		if (FD_ISSET(amaster, &rfd)) {
			n = sppd_read(amaster, buf, sizeof(buf));
			if (n < 0) {
				syslog(LOG_ERR, "Could not read master pty, " \
					"fd=%d. %s", amaster, strerror(errno));
				exit(1);
			}

			if (n == 0)
				break; /* XXX */

			if (sppd_write(s, buf, n) < 0) {
				syslog(LOG_ERR, "Could not write to socket, " \
					"fd=%d, size=%d. %s",
					s, n, strerror(errno));
				exit(1);
			}
		}

		if (FD_ISSET(s, &rfd)) {
			n = sppd_read(s, buf, sizeof(buf));
			if (n < 0) {
				syslog(LOG_ERR, "Could not read socket, " \
					"fd=%d. %s", s, strerror(errno));
				exit(1);
			}

			if (n == 0)
				break;

			if (sppd_write(fd, buf, n) < 0) {
				syslog(LOG_ERR, "Could not write to master " \
					"pty, fd=%d, size=%d. %s",
					fd, n, strerror(errno));
				exit(1);
			}
		}
	}

	syslog(LOG_INFO, "Completed on %s", (tty != NULL)? tty : "stdin/stdout");
	closelog();

	close(s);

	if (tty != NULL) {
		close(aslave);
		close(amaster);
	}	

	return (0);
}