#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  afs_ioctlnum ; 
 int /*<<< orphan*/  afs_ioctlpath ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,void*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_ioctl(void *data)
{
    int fd, ret, saved_errno;
    fd = open(afs_ioctlpath, O_RDWR);
    if (fd < 0) {
	errno = EINVAL;
	return -1;
    }
    ret = ioctl(fd, afs_ioctlnum, data);
    saved_errno = errno;
    close(fd);
    errno = saved_errno;
    return ret;
}