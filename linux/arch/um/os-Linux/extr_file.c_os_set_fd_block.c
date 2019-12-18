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

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,...) ; 

int os_set_fd_block(int fd, int blocking)
{
	int flags;

	flags = fcntl(fd, F_GETFL);
	if (flags < 0)
		return -errno;

	if (blocking)
		flags &= ~O_NONBLOCK;
	else
		flags |= O_NONBLOCK;

	if (fcntl(fd, F_SETFL, flags) < 0)
		return -errno;

	return 0;
}