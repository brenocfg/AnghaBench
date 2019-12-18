#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; int events; int /*<<< orphan*/  revents; } ;
struct TYPE_4__ {int operation; int pool; } ;
struct TYPE_5__ {scalar_t__ error; TYPE_1__ kvp_hdr; } ;
struct hv_kvp_msg {TYPE_2__ hdr; } ;
struct TYPE_6__ {int (* kvp_op_exec ) (struct hv_kvp_msg*,void*) ;} ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ HV_ERROR_NOT_SUPPORTED ; 
 int HV_KVP_OP_COUNT ; 
 int HV_KVP_OP_REGISTER ; 
 scalar_t__ HV_S_CONT ; 
 scalar_t__ HV_S_OK ; 
 int /*<<< orphan*/  INFTIM ; 
 int /*<<< orphan*/  KVP_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_USER ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  O_RDWR ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  daemon (int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int getpid () ; 
 int is_daemon ; 
 int is_debugging ; 
 scalar_t__ kvp_file_init () ; 
 TYPE_3__* kvp_op_hdlrs ; 
 scalar_t__ kvp_ops_init () ; 
 struct hv_kvp_msg* malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct hv_kvp_msg*,struct hv_kvp_msg*,int) ; 
 int /*<<< orphan*/  memset (struct hv_kvp_msg*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int pread (int,struct hv_kvp_msg*,int,int /*<<< orphan*/ ) ; 
 int pwrite (int,struct hv_kvp_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int stub1 (struct hv_kvp_msg*,void*) ; 
 int write (int,struct hv_kvp_msg*,int) ; 

int
main(int argc, char *argv[])
{
	struct hv_kvp_msg *hv_kvp_dev_buf;
	struct hv_kvp_msg *hv_msg;
	struct pollfd hv_kvp_poll_fd[1];
	int op, pool;
	int hv_kvp_dev_fd, error, len, r;
	int ch;

	while ((ch = getopt(argc, argv, "dn")) != -1) {
		switch (ch) {
		case 'n':
			/* Run as regular process for debugging purpose. */
			is_daemon = 0;
			break;
		case 'd':
			/* Generate debugging output */
			is_debugging = 1;
			break;
		default:
			break;
		}
	}

	openlog("HV_KVP", 0, LOG_USER);

	/* Become daemon first. */
	if (is_daemon == 1)
		daemon(1, 0);
	else
		KVP_LOG(LOG_DEBUG, "Run as regular process.\n");

	KVP_LOG(LOG_INFO, "HV_KVP starting; pid is: %d\n", getpid());

	/* Communication buffer hv_kvp_dev_buf */
	hv_kvp_dev_buf = malloc(sizeof(*hv_kvp_dev_buf));
	/* Buffer for daemon internal use */
	hv_msg = malloc(sizeof(*hv_msg));

	/* Memory allocation failed */
	if (hv_kvp_dev_buf == NULL || hv_msg == NULL) {
		KVP_LOG(LOG_ERR, "Failed to allocate memory for hv buffer\n");
		exit(EXIT_FAILURE);
	}

	/* Initialize op handlers */
	if (kvp_ops_init() != 0) {
		KVP_LOG(LOG_ERR, "Failed to initizlize operation handlers\n");
		exit(EXIT_FAILURE);
	}

	if (kvp_file_init()) {
		KVP_LOG(LOG_ERR, "Failed to initialize the pools\n");
		exit(EXIT_FAILURE);
	}

	/* Open the Character Device */
	hv_kvp_dev_fd = open("/dev/hv_kvp_dev", O_RDWR);

	if (hv_kvp_dev_fd < 0) {
		KVP_LOG(LOG_ERR, "open /dev/hv_kvp_dev failed; error: %d %s\n",
		    errno, strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Initialize the struct for polling the char device */
	hv_kvp_poll_fd[0].fd = hv_kvp_dev_fd;
	hv_kvp_poll_fd[0].events = (POLLIN | POLLRDNORM);

	/* Register the daemon to the KVP driver */
	memset(hv_kvp_dev_buf, 0, sizeof(*hv_kvp_dev_buf));
	hv_kvp_dev_buf->hdr.kvp_hdr.operation = HV_KVP_OP_REGISTER;
	len = write(hv_kvp_dev_fd, hv_kvp_dev_buf, sizeof(*hv_kvp_dev_buf));


	for (;;) {
		r = poll (hv_kvp_poll_fd, 1, INFTIM);

		KVP_LOG(LOG_DEBUG, "poll returned r = %d, revent = 0x%x\n",
		    r, hv_kvp_poll_fd[0].revents);

		if (r == 0 || (r < 0 && errno == EAGAIN) ||
		    (r < 0 && errno == EINTR)) {
			/* Nothing to read */
			continue;
		}

		if (r < 0) {
			/*
			 * For pread return failure other than EAGAIN,
			 * we want to exit.
			 */
			KVP_LOG(LOG_ERR, "Poll failed.\n");
			perror("poll");
			exit(EIO);
		}

		/* Read from character device */
		len = pread(hv_kvp_dev_fd, hv_kvp_dev_buf,
		    sizeof(*hv_kvp_dev_buf), 0);

		if (len < 0) {
			KVP_LOG(LOG_ERR, "Read failed.\n");
			perror("pread");
			exit(EIO);
		}

		if (len != sizeof(struct hv_kvp_msg)) {
			KVP_LOG(LOG_ERR, "read len is: %d\n", len);
			continue;
		}

		/* Copy hv_kvp_dev_buf to hv_msg */
		memcpy(hv_msg, hv_kvp_dev_buf, sizeof(*hv_msg));

		/*
		 * We will use the KVP header information to pass back
		 * the error from this daemon. So, first save the op
		 * and pool info to local variables.
		 */

		op = hv_msg->hdr.kvp_hdr.operation;
		pool = hv_msg->hdr.kvp_hdr.pool;

		if (op < 0 || op >= HV_KVP_OP_COUNT ||
		    kvp_op_hdlrs[op].kvp_op_exec == NULL) {
			KVP_LOG(LOG_WARNING,
			    "Unsupported operation OP = %d\n", op);
			hv_msg->hdr.error = HV_ERROR_NOT_SUPPORTED;
		} else {
			/*
			 * Call the operateion handler's execution routine.
			 */
			error = kvp_op_hdlrs[op].kvp_op_exec(hv_msg,
			    (void *)&kvp_op_hdlrs[op]);
			if (error != 0) {
				assert(hv_msg->hdr.error != HV_S_OK);
				if (hv_msg->hdr.error != HV_S_CONT)
					KVP_LOG(LOG_WARNING,
					    "Operation failed OP = %d, error = 0x%x\n",
					    op, error);
			}
		}

		/*
		 * Send the value back to the kernel. The response is
		 * already in the receive buffer.
		 */
hv_kvp_done:
		len = pwrite(hv_kvp_dev_fd, hv_msg, sizeof(*hv_kvp_dev_buf), 0);

		if (len != sizeof(struct hv_kvp_msg)) {
			KVP_LOG(LOG_ERR, "write len is: %d\n", len);
			goto hv_kvp_done;
		}
	}
}