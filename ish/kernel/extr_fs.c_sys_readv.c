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
struct iovec_ {unsigned int len; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int _EFAULT ; 
 int _ENOMEM ; 
 int /*<<< orphan*/  free (struct iovec_*) ; 
 struct iovec_* malloc (int) ; 
 int sys_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ user_read (int /*<<< orphan*/ ,struct iovec_*,int) ; 

dword_t sys_readv(fd_t fd_no, addr_t iovec_addr, dword_t iovec_count) {
    dword_t iovec_size = sizeof(struct iovec_) * iovec_count;
    struct iovec_ *iovecs = malloc(iovec_size);
    if (iovecs == NULL)
        return _ENOMEM;
    int res = 0;
    if (user_read(iovec_addr, iovecs, iovec_size)) {
        res = _EFAULT;
        goto err;
    }
    dword_t count = 0;
    for (unsigned i = 0; i < iovec_count; i++) {
        res = sys_read(fd_no, iovecs[i].base, iovecs[i].len);
        if (res < 0)
            goto err;
        count += res;
        if ((unsigned) res < iovecs[i].len)
            break;
    }
    free(iovecs);
    return count;

err:
    free(iovecs);
    return res;
}