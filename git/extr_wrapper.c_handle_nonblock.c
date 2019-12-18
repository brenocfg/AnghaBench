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
struct pollfd {int fd; short events; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 

__attribute__((used)) static int handle_nonblock(int fd, short poll_events, int err)
{
	struct pollfd pfd;

	if (err != EAGAIN && err != EWOULDBLOCK)
		return 0;

	pfd.fd = fd;
	pfd.events = poll_events;

	/*
	 * no need to check for errors, here;
	 * a subsequent read/write will detect unrecoverable errors
	 */
	poll(&pfd, 1, -1);
	return 1;
}