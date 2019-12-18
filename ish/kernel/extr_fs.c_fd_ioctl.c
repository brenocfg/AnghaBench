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
struct fd {TYPE_1__* ops; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ dword_t ;
struct TYPE_2__ {scalar_t__ (* ioctl_size ) (scalar_t__) ;int (* ioctl ) (struct fd*,scalar_t__,void*) ;} ;

/* Variables and functions */
 int _EFAULT ; 
 int _ENOTTY ; 
 scalar_t__ stub1 (scalar_t__) ; 
 int stub2 (struct fd*,scalar_t__,void*) ; 
 int stub3 (struct fd*,scalar_t__,char*) ; 
 scalar_t__ user_read (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ user_write (scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static int fd_ioctl(struct fd *fd, dword_t cmd, dword_t arg) {
    ssize_t size = -1;
    if (fd->ops->ioctl_size)
        size = fd->ops->ioctl_size(cmd);
    if (size < 0)
        return _ENOTTY;
    if (size == 0)
        return fd->ops->ioctl(fd, cmd, (void *) (long) arg);

    // praying that this won't break
    char buf[size];
    if (user_read(arg, buf, size))
        return _EFAULT;
    int res = fd->ops->ioctl(fd, cmd, buf);
    if (res < 0)
        return res;
    if (user_write(arg, buf, size))
        return _EFAULT;
    return res;
}