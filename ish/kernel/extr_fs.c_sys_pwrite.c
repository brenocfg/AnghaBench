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
typedef  int /*<<< orphan*/  off_t_ ;
typedef  scalar_t__ int_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  scalar_t__ dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_2__ {scalar_t__ (* lseek ) (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* write ) (struct fd*,char*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LSEEK_SET ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _EBADF ; 
 scalar_t__ _EFAULT ; 
 scalar_t__ _ENOMEM ; 
 struct fd* f_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct fd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct fd*,char*,scalar_t__) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_read (int /*<<< orphan*/ ,char*,scalar_t__) ; 

dword_t sys_pwrite(fd_t f, addr_t buf_addr, dword_t size, off_t_ off) {
    STRACE("pwrite(%d, 0x%x, %d, %d)", f, buf_addr, size, off);
    struct fd *fd = f_get(f);
    if (fd == NULL)
        return _EBADF;
    char *buf = malloc(size+1);
    if (buf == NULL)
        return _ENOMEM;
    if (user_read(buf_addr, buf, size))
        return _EFAULT;
    lock(&fd->lock);
    int_t res = fd->ops->lseek(fd, off, LSEEK_SET);
    if (res >= 0)
        res = fd->ops->write(fd, buf, size);
    unlock(&fd->lock);
    free(buf);
    return res;
}