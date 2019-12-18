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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* recv ) (int,void*,size_t,int) ;} ;

/* Variables and functions */
 scalar_t__ fd_fork_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 TYPE_1__ real ; 
 int /*<<< orphan*/  rrecv (int,void*,size_t,int) ; 
 int /*<<< orphan*/  stub1 (int,void*,size_t,int) ; 

ssize_t recv(int socket, void *buf, size_t len, int flags)
{
	int fd;
	return (fd_fork_get(socket, &fd) == fd_rsocket) ?
		rrecv(fd, buf, len, flags) : real.recv(fd, buf, len, flags);
}