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
struct TYPE_2__ {int (* getpeername ) (int,struct sockaddr*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ fd_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 TYPE_1__ real ; 
 int rgetpeername (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int stub1 (int,struct sockaddr*,int /*<<< orphan*/ *) ; 

int getpeername(int socket, struct sockaddr *addr, socklen_t *addrlen)
{
	int fd;
	return (fd_get(socket, &fd) == fd_rsocket) ?
		rgetpeername(fd, addr, addrlen) :
		real.getpeername(fd, addr, addrlen);
}