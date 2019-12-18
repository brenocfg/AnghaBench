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
struct msghdr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* recvmsg ) (int,struct msghdr*,int) ;} ;

/* Variables and functions */
 scalar_t__ fd_fork_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 TYPE_1__ real ; 
 int /*<<< orphan*/  rrecvmsg (int,struct msghdr*,int) ; 
 int /*<<< orphan*/  stub1 (int,struct msghdr*,int) ; 

ssize_t recvmsg(int socket, struct msghdr *msg, int flags)
{
	int fd;
	return (fd_fork_get(socket, &fd) == fd_rsocket) ?
		rrecvmsg(fd, msg, flags) : real.recvmsg(fd, msg, flags);
}