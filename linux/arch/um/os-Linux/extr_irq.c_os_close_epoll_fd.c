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
 int /*<<< orphan*/  epollfd ; 
 int /*<<< orphan*/  os_close_file (int /*<<< orphan*/ ) ; 

void os_close_epoll_fd(void)
{
	/* Needed so we do not leak an fd when rebooting */
	os_close_file(epollfd);
}