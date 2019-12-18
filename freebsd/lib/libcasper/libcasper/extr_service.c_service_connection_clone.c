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
struct service_connection {int dummy; } ;
struct service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_UNIX ; 
 int SOCK_NONBLOCK ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 struct service_connection* service_connection_add (struct service*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_connection_get_limits (struct service_connection*) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

int
service_connection_clone(struct service *service,
    struct service_connection *sconn)
{
	struct service_connection *newsconn;
	int serrno, sock[2];

	if (socketpair(PF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, sock) < 0)
		return (-1);

	newsconn = service_connection_add(service, sock[0],
	    service_connection_get_limits(sconn));
	if (newsconn == NULL) {
		serrno = errno;
		close(sock[0]);
		close(sock[1]);
		errno = serrno;
		return (-1);
	}

	return (sock[1]);
}