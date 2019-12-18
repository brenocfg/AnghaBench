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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  server_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDPD ; 
 char* SDP_LOCAL_PATH ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ done ; 
 scalar_t__ drop_root (char const*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  log_close () ; 
 int /*<<< orphan*/  log_crit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 scalar_t__ server_do (int /*<<< orphan*/ *) ; 
 scalar_t__ server_init (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  server_shutdown (int /*<<< orphan*/ *) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	server_t		 server;
	char const		*control = SDP_LOCAL_PATH;
	char const		*user = "nobody", *group = "nobody";
	int32_t			 detach = 1, opt;
	struct sigaction	 sa;

	while ((opt = getopt(argc, argv, "c:dg:hu:")) != -1) {
		switch (opt) {
		case 'c': /* control */
			control = optarg;
			break;

		case 'd': /* do not detach */
			detach = 0;
			break;

		case 'g': /* group */
			group = optarg;
			break;

		case 'u': /* user */
			user = optarg;
			break;

		case 'h':
		default:
			usage();
			/* NOT REACHED */
		}
	}

	log_open(SDPD, !detach);

	/* Become daemon if required */
	if (detach && daemon(0, 0) < 0) {
		log_crit("Could not become daemon. %s (%d)",
			strerror(errno), errno);
		exit(1);
	}

	/* Set signal handlers */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sighandler;

	if (sigaction(SIGTERM, &sa, NULL) < 0 ||
	    sigaction(SIGHUP,  &sa, NULL) < 0 ||
	    sigaction(SIGINT,  &sa, NULL) < 0) {
		log_crit("Could not install signal handlers. %s (%d)",
			strerror(errno), errno); 
		exit(1);
	}

	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGPIPE, &sa, NULL) < 0) {
		log_crit("Could not install signal handlers. %s (%d)",
			strerror(errno), errno); 
		exit(1);
	}

	/* Initialize server */
	if (server_init(&server, control) < 0)
		exit(1);

	if ((user != NULL || group != NULL) && drop_root(user, group) < 0)
		exit(1);

	for (done = 0; !done; ) {
		if (server_do(&server) != 0)
			done ++;
	}

	server_shutdown(&server);
	log_close();

	return (0);
}