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
struct iscsi_daemon_fail {int /*<<< orphan*/  idf_reason; int /*<<< orphan*/  idf_session_id; } ;
struct connection {int /*<<< orphan*/  conn_iscsi_fd; int /*<<< orphan*/  conn_session_id; } ;
typedef  int /*<<< orphan*/  idf ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSIDFAIL ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iscsi_daemon_fail*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  memset (struct iscsi_daemon_fail*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

void
fail(const struct connection *conn, const char *reason)
{
	struct iscsi_daemon_fail idf;
	int error, saved_errno;

	saved_errno = errno;

	memset(&idf, 0, sizeof(idf));
	idf.idf_session_id = conn->conn_session_id;
	strlcpy(idf.idf_reason, reason, sizeof(idf.idf_reason));

	error = ioctl(conn->conn_iscsi_fd, ISCSIDFAIL, &idf);
	if (error != 0)
		log_err(1, "ISCSIDFAIL");

	errno = saved_errno;
}