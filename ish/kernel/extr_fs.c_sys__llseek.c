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
struct fd {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
typedef  int off_t_ ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {int (* lseek ) (struct fd*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int,...) ; 
 int _EBADF ; 
 int _EFAULT ; 
 int _ESPIPE ; 
 struct fd* f_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int stub1 (struct fd*,int,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,int) ; 

dword_t sys__llseek(fd_t f, dword_t off_high, dword_t off_low, addr_t res_addr, dword_t whence) {
    struct fd *fd = f_get(f);
    if (fd == NULL)
        return _EBADF;
    if (!fd->ops->lseek)
        return _ESPIPE;
    lock(&fd->lock);
    off_t_ off = ((off_t_) off_high << 32) | off_low;
    STRACE("llseek(%d, %lu, %#x, %d)", f, off, res_addr, whence);
    off_t_ res = fd->ops->lseek(fd, off, whence);
    STRACE(" -> %lu", res);
    unlock(&fd->lock);
    if (res < 0)
        return res;
    if (user_put(res_addr, res))
        return _EFAULT;
    return 0;
}