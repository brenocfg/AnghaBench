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
 scalar_t__ uc_socket_connect (int) ; 
 scalar_t__ uc_sync_recv () ; 

__attribute__((used)) static int
t_peercred_client(int fd)
{
	struct xucred xucred;
	socklen_t len;

	if (uc_sync_recv() < 0)
		return (-1);

	if (uc_socket_connect(fd) < 0)
		return (-1);

	len = sizeof(xucred);
	if (getsockopt(fd, 0, LOCAL_PEERCRED, &xucred, &len) < 0) {
		uc_logmsg("getsockopt(LOCAL_PEERCRED)");
		return (-1);
	}

	if (check_xucred(&xucred, len) < 0)
		return (-1);

	return (0);
}