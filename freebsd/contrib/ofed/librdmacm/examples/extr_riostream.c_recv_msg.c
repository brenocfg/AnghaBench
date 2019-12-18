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
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ buf ; 
 int do_poll (struct pollfd*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll_timeout ; 
 int rrecv (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs ; 
 scalar_t__ use_async ; 

__attribute__((used)) static int recv_msg(int size)
{
	struct pollfd fds;
	int offset, ret;

	if (use_async) {
		fds.fd = rs;
		fds.events = POLLIN;
	}

	for (offset = 0; offset < size; ) {
		if (use_async) {
			ret = do_poll(&fds, poll_timeout);
			if (ret)
				return ret;
		}

		ret = rrecv(rs, buf + offset, size - offset, flags);
		if (ret > 0) {
			offset += ret;
		} else if (errno != EWOULDBLOCK && errno != EAGAIN) {
			perror("rrecv");
			return ret;
		}
	}

	return 0;
}