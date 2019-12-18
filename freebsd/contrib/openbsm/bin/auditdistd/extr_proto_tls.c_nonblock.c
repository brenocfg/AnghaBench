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
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
nonblock(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL);
	if (flags == -1)
		pjdlog_exit(EX_TEMPFAIL, "fcntl(F_GETFL) failed");
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) == -1)
		pjdlog_exit(EX_TEMPFAIL, "fcntl(F_SETFL) failed");
}