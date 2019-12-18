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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int (* sendfile ) (int,int,int /*<<< orphan*/ *,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ fd_get (int,int*) ; 
 scalar_t__ fd_rsocket ; 
 int /*<<< orphan*/  lseek (int,size_t,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 TYPE_1__ real ; 
 size_t rwrite (int,void*,size_t) ; 
 int stub1 (int,int,int /*<<< orphan*/ *,size_t) ; 

ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count)
{
	void *file_addr;
	int fd;
	size_t ret;

	if (fd_get(out_fd, &fd) != fd_rsocket)
		return real.sendfile(fd, in_fd, offset, count);

	file_addr = mmap(NULL, count, PROT_READ, 0, in_fd, offset ? *offset : 0);
	if (file_addr == (void *) -1)
		return -1;

	ret = rwrite(fd, file_addr, count);
	if ((ret > 0) && offset)
		lseek(in_fd, ret, SEEK_CUR);
	munmap(file_addr, count);
	return ret;
}