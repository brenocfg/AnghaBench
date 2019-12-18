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
typedef  int /*<<< orphan*/  xucred ;
struct xucred {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_PEERCRED ; 
 scalar_t__ check_xucred (struct xucred*,int) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xucred*,int*) ; 
 int /*<<< orphan*/  uc_logmsg (char*) ; 
 int uc_socket_accept (int) ; 
 scalar_t__ uc_socket_close (int) ; 
 scalar_t__ uc_sync_send () ; 

__attribute__((used)) static int
t_peercred_server(int fd1)
{
	struct xucred xucred;
	socklen_t len;
	int fd2, rv;

	if (uc_sync_send() < 0)
		return (-2);

	fd2 = uc_socket_accept(fd1);
	if (fd2 < 0)
		return (-2);

	len = sizeof(xucred);
	if (getsockopt(fd2, 0, LOCAL_PEERCRED, &xucred, &len) < 0) {
		uc_logmsg("getsockopt(LOCAL_PEERCRED)");
		rv = -2;
		goto done;
	}

	if (check_xucred(&xucred, len) < 0) {
		rv = -1;
		goto done;
	}

	rv = 0;
done:
	if (uc_socket_close(fd2) < 0)
		rv = -2;
	return (rv);
}