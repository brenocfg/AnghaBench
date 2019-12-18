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
union socket_addr {int /*<<< orphan*/  sa; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct message {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ do_poll (struct pollfd*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll_timeout ; 
 int /*<<< orphan*/  rs ; 
 scalar_t__ rs_recvfrom (int /*<<< orphan*/ ,struct message*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ use_async ; 

__attribute__((used)) static ssize_t svr_recv(struct message *msg, size_t size,
			union socket_addr *addr, socklen_t *addrlen)
{
	struct pollfd fds;
	ssize_t ret;

	if (use_async) {
		fds.fd = rs;
		fds.events = POLLIN;
	}

	do {
		if (use_async) {
			ret = do_poll(&fds, poll_timeout);
			if (ret)
				return ret;
		}

		ret = rs_recvfrom(rs, msg, size, flags, &addr->sa, addrlen);
	} while (ret < 0 && (errno == EWOULDBLOCK || errno == EAGAIN));

	if (ret < 0)
		perror("rrecv");

	return ret;
}