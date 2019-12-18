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
struct stat {scalar_t__ st_mode; } ;
struct hast_resource {scalar_t__ hr_role; int /*<<< orphan*/  hr_name; int /*<<< orphan*/ * hr_remoteout; int /*<<< orphan*/ * hr_remotein; int /*<<< orphan*/ * hr_conn; int /*<<< orphan*/ * hr_ctrl; int /*<<< orphan*/ * hr_event; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  scalar_t__ mode_t ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ HAST_ROLE_PRIMARY ; 
 scalar_t__ HAST_ROLE_SECONDARY ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,char*) ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 scalar_t__ S_IFSOCK ; 
 int /*<<< orphan*/  S_ISSOCK (scalar_t__) ; 
 int /*<<< orphan*/  _SC_OPEN_MAX ; 
 char* dtype2str (scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_fini () ; 
 int /*<<< orphan*/  pjdlog_init (int) ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int proto_descriptor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  role2str (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 char* strerror (scalar_t__) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

void
descriptors_assert(const struct hast_resource *res, int pjdlogmode)
{
	char msg[256];
	struct stat sb;
	long maxfd;
	bool isopen;
	mode_t mode;
	int fd;

	/*
	 * At this point descriptor to syslog socket is closed, so if we want
	 * to log assertion message, we have to first store it in 'msg' local
	 * buffer and then open syslog socket and log it.
	 */
	msg[0] = '\0';

	maxfd = sysconf(_SC_OPEN_MAX);
	if (maxfd == -1) {
		pjdlog_init(pjdlogmode);
		pjdlog_prefix_set("[%s] (%s) ", res->hr_name,
		    role2str(res->hr_role));
		pjdlog_errno(LOG_WARNING, "sysconf(_SC_OPEN_MAX) failed");
		pjdlog_fini();
		maxfd = 16384;
	}
	for (fd = 0; fd <= maxfd; fd++) {
		if (fstat(fd, &sb) == 0) {
			isopen = true;
			mode = sb.st_mode;
		} else if (errno == EBADF) {
			isopen = false;
			mode = 0;
		} else {
			(void)snprintf(msg, sizeof(msg),
			    "Unable to fstat descriptor %d: %s", fd,
			    strerror(errno));
			break;
		}
		if (fd == STDIN_FILENO || fd == STDOUT_FILENO ||
		    fd == STDERR_FILENO) {
			if (!isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (%s) is closed, but should be open.",
				    fd, (fd == STDIN_FILENO ? "stdin" :
				    (fd == STDOUT_FILENO ? "stdout" : "stderr")));
				break;
			}
		} else if (fd == proto_descriptor(res->hr_event)) {
			if (!isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (event) is closed, but should be open.",
				    fd);
				break;
			}
			if (!S_ISSOCK(mode)) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (event) is %s, but should be %s.",
				    fd, dtype2str(mode), dtype2str(S_IFSOCK));
				break;
			}
		} else if (fd == proto_descriptor(res->hr_ctrl)) {
			if (!isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (ctrl) is closed, but should be open.",
				    fd);
				break;
			}
			if (!S_ISSOCK(mode)) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (ctrl) is %s, but should be %s.",
				    fd, dtype2str(mode), dtype2str(S_IFSOCK));
				break;
			}
		} else if (res->hr_role == HAST_ROLE_PRIMARY &&
		    fd == proto_descriptor(res->hr_conn)) {
			if (!isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (conn) is closed, but should be open.",
				    fd);
				break;
			}
			if (!S_ISSOCK(mode)) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (conn) is %s, but should be %s.",
				    fd, dtype2str(mode), dtype2str(S_IFSOCK));
				break;
			}
		} else if (res->hr_role == HAST_ROLE_SECONDARY &&
		    res->hr_conn != NULL &&
		    fd == proto_descriptor(res->hr_conn)) {
			if (isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (conn) is open, but should be closed.",
				    fd);
				break;
			}
		} else if (res->hr_role == HAST_ROLE_SECONDARY &&
		    fd == proto_descriptor(res->hr_remotein)) {
			if (!isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (remote in) is closed, but should be open.",
				    fd);
				break;
			}
			if (!S_ISSOCK(mode)) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (remote in) is %s, but should be %s.",
				    fd, dtype2str(mode), dtype2str(S_IFSOCK));
				break;
			}
		} else if (res->hr_role == HAST_ROLE_SECONDARY &&
		    fd == proto_descriptor(res->hr_remoteout)) {
			if (!isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (remote out) is closed, but should be open.",
				    fd);
				break;
			}
			if (!S_ISSOCK(mode)) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d (remote out) is %s, but should be %s.",
				    fd, dtype2str(mode), dtype2str(S_IFSOCK));
				break;
			}
		} else {
			if (isopen) {
				(void)snprintf(msg, sizeof(msg),
				    "Descriptor %d is open (%s), but should be closed.",
				    fd, dtype2str(mode));
				break;
			}
		}
	}
	if (msg[0] != '\0') {
		pjdlog_init(pjdlogmode);
		pjdlog_prefix_set("[%s] (%s) ", res->hr_name,
		    role2str(res->hr_role));
		PJDLOG_ABORT("%s", msg);
	}
}