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
struct iscsi_daemon_request {int dummy; } ;
typedef  int /*<<< orphan*/  request ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 char* DEFAULT_PIDFILE ; 
 int EEXIST ; 
 int EINTR ; 
 int ENOENT ; 
 int /*<<< orphan*/  ISCSIDWAIT ; 
 int /*<<< orphan*/  ISCSI_PATH ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 int daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_request (int,struct iscsi_daemon_request*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct iscsi_daemon_request*) ; 
 int kldload (char*) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_err (int,char*,...) ; 
 int /*<<< orphan*/  log_errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_init (int) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  memset (struct iscsi_daemon_request*,int /*<<< orphan*/ ,int) ; 
 int nchildren ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pidfile_close (struct pidfh*) ; 
 struct pidfh* pidfile_open (char const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 
 int /*<<< orphan*/  pidfile_write (struct pidfh*) ; 
 int /*<<< orphan*/  register_sigchld () ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ wait_for_children (int) ; 

int
main(int argc, char **argv)
{
	int ch, debug = 0, error, iscsi_fd, maxproc = 30, retval, saved_errno,
	    timeout = 60;
	bool dont_daemonize = false;
	struct pidfh *pidfh;
	pid_t pid, otherpid;
	const char *pidfile_path = DEFAULT_PIDFILE;
	struct iscsi_daemon_request request;

	while ((ch = getopt(argc, argv, "P:dl:m:t:")) != -1) {
		switch (ch) {
		case 'P':
			pidfile_path = optarg;
			break;
		case 'd':
			dont_daemonize = true;
			debug++;
			break;
		case 'l':
			debug = atoi(optarg);
			break;
		case 'm':
			maxproc = atoi(optarg);
			break;
		case 't':
			timeout = atoi(optarg);
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	if (argc != 0)
		usage();

	log_init(debug);

	pidfh = pidfile_open(pidfile_path, 0600, &otherpid);
	if (pidfh == NULL) {
		if (errno == EEXIST)
			log_errx(1, "daemon already running, pid: %jd.",
			    (intmax_t)otherpid);
		log_err(1, "cannot open or create pidfile \"%s\"",
		    pidfile_path);
	}

	iscsi_fd = open(ISCSI_PATH, O_RDWR);
	if (iscsi_fd < 0 && errno == ENOENT) {
		saved_errno = errno;
		retval = kldload("iscsi");
		if (retval != -1)
			iscsi_fd = open(ISCSI_PATH, O_RDWR);
		else
			errno = saved_errno;
	}
	if (iscsi_fd < 0)
		log_err(1, "failed to open %s", ISCSI_PATH);

	if (dont_daemonize == false) {
		if (daemon(0, 0) == -1) {
			log_warn("cannot daemonize");
			pidfile_remove(pidfh);
			exit(1);
		}
	}

	pidfile_write(pidfh);

	register_sigchld();

	for (;;) {
		log_debugx("waiting for request from the kernel");

		memset(&request, 0, sizeof(request));
		error = ioctl(iscsi_fd, ISCSIDWAIT, &request);
		if (error != 0) {
			if (errno == EINTR) {
				nchildren -= wait_for_children(false);
				assert(nchildren >= 0);
				continue;
			}

			log_err(1, "ISCSIDWAIT");
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
			log_debugx("incoming connection; forking child process #%d",
			    nchildren);
			nchildren++;

			pid = fork();
			if (pid < 0)
				log_err(1, "fork");
			if (pid > 0)
				continue;
		}

		pidfile_close(pidfh);
		handle_request(iscsi_fd, &request, timeout);
	}

	return (0);
}