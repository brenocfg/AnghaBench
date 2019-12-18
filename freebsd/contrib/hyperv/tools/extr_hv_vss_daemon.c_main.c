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
typedef  int uint32_t ;
struct pollfd {int fd; int events; char* revents; } ;
struct hv_vss_opt_msg {int status; int opt; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FS_VSS_DEV_NAME ; 
#define  HV_VSS_CHECK 130 
#define  HV_VSS_FREEZE 129 
#define  HV_VSS_THAW 128 
 int /*<<< orphan*/  INFTIM ; 
 int /*<<< orphan*/  IOCHVVSSREAD ; 
 int /*<<< orphan*/  IOCHVVSSWRITE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_USER ; 
 int /*<<< orphan*/  O_RDWR ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  VSS_DEV (int /*<<< orphan*/ ) ; 
 void* VSS_FAIL ; 
 int /*<<< orphan*/  VSS_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int VSS_SUCCESS ; 
 int check () ; 
 int /*<<< orphan*/  daemon (int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int freeze () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int ioctl (int,int /*<<< orphan*/ ,struct hv_vss_opt_msg*) ; 
 int is_daemon ; 
 int is_debugging ; 
 int /*<<< orphan*/  memset (struct hv_vss_opt_msg*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int thaw () ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char* argv[])
{
	struct hv_vss_opt_msg  userdata;

	struct pollfd hv_vss_poll_fd[1];
	uint32_t op;
	int ch, r, error;
	int hv_vss_dev_fd;

	while ((ch = getopt(argc, argv, "dnh")) != -1) {
		switch (ch) {
		case 'n':
			/* Run as regular process for debugging purpose. */
			is_daemon = 0;
			break;
		case 'd':
			/* Generate debugging output */
			is_debugging = 1;
			break;
		case 'h':
		default:
			usage(argv[0]);
			break;
		}
	}

	openlog("HV_VSS", 0, LOG_USER);

	/* Become daemon first. */
	if (is_daemon == 1)
		daemon(1, 0);
	else
		VSS_LOG(LOG_DEBUG, "Run as regular process.\n");

	VSS_LOG(LOG_INFO, "HV_VSS starting; pid is: %d\n", getpid());

	memset(&userdata, 0, sizeof(struct hv_vss_opt_msg));
	/* register the daemon */
	hv_vss_dev_fd = open(VSS_DEV(FS_VSS_DEV_NAME), O_RDWR);

	if (hv_vss_dev_fd < 0) {
		VSS_LOG(LOG_ERR, "Fail to open %s, error: %d %s\n",
		    VSS_DEV(FS_VSS_DEV_NAME), errno, strerror(errno));
		exit(EXIT_FAILURE);
	}
	hv_vss_poll_fd[0].fd = hv_vss_dev_fd;
	hv_vss_poll_fd[0].events = POLLIN | POLLRDNORM;

	while (1) {
		r = poll(hv_vss_poll_fd, 1, INFTIM);

		VSS_LOG(LOG_DEBUG, "poll returned r = %d, revent = 0x%x\n",
		    r, hv_vss_poll_fd[0].revents);

		if (r == 0 || (r < 0 && errno == EAGAIN) ||
		    (r < 0 && errno == EINTR)) {
			/* Nothing to read */
			continue;
		}

		if (r < 0) {
			/*
			 * For poll return failure other than EAGAIN,
			 * we want to exit.
			 */
			VSS_LOG(LOG_ERR, "Poll failed.\n");
			perror("poll");
			exit(EIO);
		}

		/* Read from character device */
		error = ioctl(hv_vss_dev_fd, IOCHVVSSREAD, &userdata);
		if (error < 0) {
			VSS_LOG(LOG_ERR, "Read failed.\n");
			perror("pread");
			exit(EIO);
		}

		if (userdata.status != 0) {
			VSS_LOG(LOG_ERR, "data read error\n");
			continue;
		}

		/*
		 * We will use the KVP header information to pass back
		 * the error from this daemon. So, first save the op
		 * and pool info to local variables.
		 */

		op = userdata.opt;

		switch (op) {
		case HV_VSS_CHECK:
			error = check();
			break;
		case HV_VSS_FREEZE:
			error = freeze();
			break;
		case HV_VSS_THAW:
			error = thaw();
			break;
		default:
			VSS_LOG(LOG_ERR, "Illegal operation: %d\n", op);
			error = VSS_FAIL;
		}
		if (error)
			userdata.status = VSS_FAIL;
		else
			userdata.status = VSS_SUCCESS;
		error = ioctl(hv_vss_dev_fd, IOCHVVSSWRITE, &userdata);
		if (error != 0) {
			VSS_LOG(LOG_ERR, "Fail to write to device\n");
			exit(EXIT_FAILURE);
		} else {
			VSS_LOG(LOG_INFO, "Send response %d for %s to kernel\n",
			    userdata.status, op == HV_VSS_FREEZE ? "Freeze" :
			    (op == HV_VSS_THAW ? "Thaw" : "Check"));
		}
	}
}