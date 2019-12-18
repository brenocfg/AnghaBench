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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {int (* accept ) (int,struct sockaddr*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fd_close (int,int*) ; 
 scalar_t__ fd_fork_listen ; 
 int /*<<< orphan*/  fd_fork_passive ; 
 scalar_t__ fd_get (int,int*) ; 
 scalar_t__ fd_gets (int) ; 
 scalar_t__ fd_normal ; 
 int fd_open () ; 
 int /*<<< orphan*/  fd_ready ; 
 scalar_t__ fd_rsocket ; 
 int /*<<< orphan*/  fd_store (int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int raccept (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 TYPE_1__ real ; 
 int stub1 (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int stub2 (int,struct sockaddr*,int /*<<< orphan*/ *) ; 

int accept(int socket, struct sockaddr *addr, socklen_t *addrlen)
{
	int fd, index, ret;

	if (fd_get(socket, &fd) == fd_rsocket) {
		index = fd_open();
		if (index < 0)
			return index;

		ret = raccept(fd, addr, addrlen);
		if (ret < 0) {
			fd_close(index, &fd);
			return ret;
		}

		fd_store(index, ret, fd_rsocket, fd_ready);
		return index;
	} else if (fd_gets(socket) == fd_fork_listen) {
		index = fd_open();
		if (index < 0)
			return index;

		ret = real.accept(fd, addr, addrlen);
		if (ret < 0) {
			fd_close(index, &fd);
			return ret;
		}

		fd_store(index, ret, fd_normal, fd_fork_passive);
		return index;
	} else {
		return real.accept(fd, addr, addrlen);
	}
}