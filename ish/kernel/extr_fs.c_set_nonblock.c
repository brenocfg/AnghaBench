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
struct fd {int dummy; } ;
typedef  scalar_t__ dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int O_NONBLOCK_ ; 
 int _EFAULT ; 
 int fd_getflags (struct fd*) ; 
 int fd_setflags (struct fd*,int) ; 
 scalar_t__ user_get (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int set_nonblock(struct fd *fd, addr_t nb_addr) {
    dword_t nonblock;
    if (user_get(nb_addr, nonblock))
        return _EFAULT;
    int flags = fd_getflags(fd);
    if (nonblock)
        flags |= O_NONBLOCK_;
    else
        flags &= ~O_NONBLOCK_;
    return fd_setflags(fd, flags);
}