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
struct rt_msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int LOG_CONS ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int LOG_UPTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_ROUTE ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int discover_on_join ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_rtmsg (struct rt_msghdr*,int /*<<< orphan*/ ) ; 
 char** ifnets ; 
 int nifnets ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 int /*<<< orphan*/  scanforvaps (int) ; 
 void* script ; 
 int /*<<< orphan*/  setlogmask (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage (char const*) ; 

int
main(int argc, char *argv[])
{
	const char *progname = argv[0];
	const char *pidfile = NULL;
	int s, c, logmask, bg = 1;
	char msg[2048];
	int log_stderr = 0;

	logmask = LOG_UPTO(LOG_INFO);
	while ((c = getopt(argc, argv, "efjP:s:tv")) != -1)
		switch (c) {
		case 'e':
			log_stderr = LOG_PERROR;
			break;
		case 'f':
			bg = 0;
			break;
		case 'j':
			discover_on_join = 1;
			break;
		case 'P':
			pidfile = optarg;
			break;
		case 's':
			script = optarg;
			break;
		case 't':
			logmask = LOG_UPTO(LOG_ERR);
			break;
		case 'v':
			logmask = LOG_UPTO(LOG_DEBUG);
			break;
		case '?':
			usage(progname);
			/*NOTREACHED*/
		}
	argc -= optind, argv += optind;
	if (argc == 0) {
		fprintf(stderr, "%s: no ifnet's specified to monitor\n",
		    progname);
		usage(progname);
	}
	ifnets = argv;
	nifnets = argc;

	s = socket(PF_ROUTE, SOCK_RAW, 0);
	if (s < 0)
		err(EX_OSERR, "socket");
	/*
	 * Scan for inherited state.
	 */
	scanforvaps(s);

	/* XXX what directory to work in? */
	if (bg && daemon(0, 0) < 0)
		err(EX_OSERR, "daemon");

	openlog("wlanwds", log_stderr | LOG_PID | LOG_CONS, LOG_DAEMON);
	setlogmask(logmask);

	for (;;) {
		ssize_t n = read(s, msg, sizeof(msg));
		handle_rtmsg((struct rt_msghdr *)msg, n);
	}
	return 0;
}