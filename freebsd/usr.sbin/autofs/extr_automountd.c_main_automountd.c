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
struct pidfh {int dummy; } ;
struct autofs_daemon_request {int dummy; } ;
typedef  int /*<<< orphan*/  request ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFSREQUEST ; 
 int /*<<< orphan*/  AUTOFS_PATH ; 
 char* AUTOMOUNTD_PIDFILE ; 
 int EEXIST ; 
 int EINTR ; 
 int ENOENT ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_fd ; 
 char* concat (char*,char,int /*<<< orphan*/ ) ; 
 int daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defined_init () ; 
 int /*<<< orphan*/  defined_parse_and_add (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_request (struct autofs_daemon_request*,char*,int) ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,struct autofs_daemon_request*) ; 
 int kldload (char*) ; 
 int /*<<< orphan*/  lesser_daemon () ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_err (int,char*,...) ; 
 int /*<<< orphan*/  log_errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_init (int) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  memset (struct autofs_daemon_request*,int /*<<< orphan*/ ,int) ; 
 int nchildren ; 
 scalar_t__ open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pidfile_close (struct pidfh*) ; 
 struct pidfh* pidfile_open (char const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 
 int /*<<< orphan*/  pidfile_write (struct pidfh*) ; 
 int /*<<< orphan*/  register_sigchld () ; 
 int /*<<< orphan*/  usage_automountd () ; 
 scalar_t__ wait_for_children (int) ; 

int
main_automountd(int argc, char **argv)
{
	struct pidfh *pidfh;
	pid_t pid, otherpid;
	const char *pidfile_path = AUTOMOUNTD_PIDFILE;
	char *options = NULL;
	struct autofs_daemon_request request;
	int ch, debug = 0, error, maxproc = 30, retval, saved_errno;
	bool dont_daemonize = false, incomplete_hierarchy = false;

	defined_init();

	while ((ch = getopt(argc, argv, "D:Tdim:o:v")) != -1) {
		switch (ch) {
		case 'D':
			defined_parse_and_add(optarg);
			break;
		case 'T':
			/*
			 * For compatibility with other implementations,
			 * such as OS X.
			 */
			debug++;
			break;
		case 'd':
			dont_daemonize = true;
			debug++;
			break;
		case 'i':
			incomplete_hierarchy = true;
			break;
		case 'm':
			maxproc = atoi(optarg);
			break;
		case 'o':
			options = concat(options, ',', optarg);
			break;
		case 'v':
			debug++;
			break;
		case '?':
		default:
			usage_automountd();
		}
	}
	argc -= optind;
	if (argc != 0)
		usage_automountd();

	log_init(debug);

	pidfh = pidfile_open(pidfile_path, 0600, &otherpid);
	if (pidfh == NULL) {
		if (errno == EEXIST) {
			log_errx(1, "daemon already running, pid: %jd.",
			    (intmax_t)otherpid);
		}
		log_err(1, "cannot open or create pidfile \"%s\"",
		    pidfile_path);
	}

	autofs_fd = open(AUTOFS_PATH, O_RDWR | O_CLOEXEC);
	if (autofs_fd < 0 && errno == ENOENT) {
		saved_errno = errno;
		retval = kldload("autofs");
		if (retval != -1)
			autofs_fd = open(AUTOFS_PATH, O_RDWR | O_CLOEXEC);
		else
			errno = saved_errno;
	}
	if (autofs_fd < 0)
		log_err(1, "failed to open %s", AUTOFS_PATH);

	if (dont_daemonize == false) {
		if (daemon(0, 0) == -1) {
			log_warn("cannot daemonize");
			pidfile_remove(pidfh);
			exit(1);
		}
	} else {
		lesser_daemon();
	}

	pidfile_write(pidfh);

	register_sigchld();

	for (;;) {
		log_debugx("waiting for request from the kernel");

		memset(&request, 0, sizeof(request));
		error = ioctl(autofs_fd, AUTOFSREQUEST, &request);
		if (error != 0) {
			if (errno == EINTR) {
				nchildren -= wait_for_children(false);
				assert(nchildren >= 0);
				continue;
			}

			log_err(1, "AUTOFSREQUEST");
		}

		if (dont_daemonize) {
			log_debugx("not forking due to -d flag; "
			    "will exit after servicing a single request");
		} else {
			nchildren -= wait_for_children(false);
			assert(nchildren >= 0);

			while (maxproc > 0 && nchildren >= maxproc) {
				log_debugx("maxproc limit of %d child processes hit; "
				    "waiting for child process to exit", maxproc);
				nchildren -= wait_for_children(true);
				assert(nchildren >= 0);
			}
			log_debugx("got request; forking child process #%d",
			    nchildren);
			nchildren++;

			pid = fork();
			if (pid < 0)
				log_err(1, "fork");
			if (pid > 0)
				continue;
		}

		pidfile_close(pidfh);
		handle_request(&request, options, incomplete_hierarchy);
	}

	pidfile_close(pidfh);

	return (0);
}