#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* listen ) (int,int) ;} ;

/* Variables and functions */
 scalar_t__ fd_fork ; 
 int /*<<< orphan*/  fd_fork_listen ; 
 scalar_t__ fd_get (int,int*) ; 
 scalar_t__ fd_gets (int) ; 
 int /*<<< orphan*/  fd_normal ; 
 scalar_t__ fd_rsocket ; 
 int /*<<< orphan*/  fd_store (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ real ; 
 int rlisten (int,int) ; 
 int stub1 (int,int) ; 

int listen(int socket, int backlog)
{
	int fd, ret;
	if (fd_get(socket, &fd) == fd_rsocket) {
		ret = rlisten(fd, backlog);
	} else {
		ret = real.listen(fd, backlog);
		if (!ret && fd_gets(socket) == fd_fork)
			fd_store(socket, fd, fd_normal, fd_fork_listen);
	}
	return ret;
}