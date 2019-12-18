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
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* readv ) (int,struct iovec const*,int) ;} ;

/* Variables and functions */
 scalar_t__ fd_fork_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 int /*<<< orphan*/  init_preload () ; 
 TYPE_1__ real ; 
 int /*<<< orphan*/  rreadv (int,struct iovec const*,int) ; 
 int /*<<< orphan*/  stub1 (int,struct iovec const*,int) ; 

ssize_t readv(int socket, const struct iovec *iov, int iovcnt)
{
	int fd;
	init_preload();
	return (fd_fork_get(socket, &fd) == fd_rsocket) ?
		rreadv(fd, iov, iovcnt) : real.readv(fd, iov, iovcnt);
}