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
struct pollfd {int /*<<< orphan*/  events; scalar_t__ fd; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  POLLIN ; 
 int do_poll (struct pollfd*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  fork_pid ; 
 scalar_t__ lrs ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll_timeout ; 
 scalar_t__ rs ; 
 scalar_t__ rs_accept (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_options (scalar_t__) ; 
 scalar_t__ use_async ; 
 scalar_t__ use_fork ; 

__attribute__((used)) static int server_connect(void)
{
	struct pollfd fds;
	int ret = 0;

	set_options(lrs);
	do {
		if (use_async) {
			fds.fd = lrs;
			fds.events = POLLIN;

			ret = do_poll(&fds, poll_timeout);
			if (ret) {
				perror("rpoll");
				return ret;
			}
		}

		rs = rs_accept(lrs, NULL, NULL);
	} while (rs < 0 && (errno == EAGAIN || errno == EWOULDBLOCK));
	if (rs < 0) {
		perror("raccept");
		return rs;
	}

	if (use_fork)
		fork_pid = fork();
	if (!fork_pid)
		set_options(rs);
	return ret;
}