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
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (int,void*,size_t) ;} ;

/* Variables and functions */
 scalar_t__ fd_fork_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 int /*<<< orphan*/  init_preload () ; 
 TYPE_1__ real ; 
 int /*<<< orphan*/  rread (int,void*,size_t) ; 
 int /*<<< orphan*/  stub1 (int,void*,size_t) ; 

ssize_t read(int socket, void *buf, size_t count)
{
	int fd;
	init_preload();
	return (fd_fork_get(socket, &fd) == fd_rsocket) ?
		rread(fd, buf, count) : real.read(fd, buf, count);
}