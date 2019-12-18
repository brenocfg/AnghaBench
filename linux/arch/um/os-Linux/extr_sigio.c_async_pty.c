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
 int /*<<< orphan*/  F_SETOWN ; 
 int O_ASYNC ; 
 int O_NONBLOCK ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int os_getpid () ; 

__attribute__((used)) static int async_pty(int master, int slave)
{
	int flags;

	flags = fcntl(master, F_GETFL);
	if (flags < 0)
		return -errno;

	if ((fcntl(master, F_SETFL, flags | O_NONBLOCK | O_ASYNC) < 0) ||
	    (fcntl(master, F_SETOWN, os_getpid()) < 0))
		return -errno;

	if ((fcntl(slave, F_SETFL, flags | O_NONBLOCK) < 0))
		return -errno;

	return 0;
}