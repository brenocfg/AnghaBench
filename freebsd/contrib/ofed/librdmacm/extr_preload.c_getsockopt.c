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
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {int (* getsockopt ) (int,int,int,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ fd_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 TYPE_1__ real ; 
 int rgetsockopt (int,int,int,void*,int /*<<< orphan*/ *) ; 
 int stub1 (int,int,int,void*,int /*<<< orphan*/ *) ; 

int getsockopt(int socket, int level, int optname,
		void *optval, socklen_t *optlen)
{
	int fd;
	return (fd_get(socket, &fd) == fd_rsocket) ?
		rgetsockopt(fd, level, optname, optval, optlen) :
		real.getsockopt(fd, level, optname, optval, optlen);
}