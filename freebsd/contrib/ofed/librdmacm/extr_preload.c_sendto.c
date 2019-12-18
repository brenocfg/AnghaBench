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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* sendto ) (int,void const*,size_t,int,struct sockaddr const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ fd_fork_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 TYPE_1__ real ; 
 int /*<<< orphan*/  rsendto (int,void const*,size_t,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,void const*,size_t,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

ssize_t sendto(int socket, const void *buf, size_t len, int flags,
		const struct sockaddr *dest_addr, socklen_t addrlen)
{
	int fd;
	return (fd_fork_get(socket, &fd) == fd_rsocket) ?
		rsendto(fd, buf, len, flags, dest_addr, addrlen) :
		real.sendto(fd, buf, len, flags, dest_addr, addrlen);
}