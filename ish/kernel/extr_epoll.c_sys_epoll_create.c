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
struct TYPE_2__ {int /*<<< orphan*/  poll; } ;
struct fd {TYPE_1__ epollfd; } ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  fd_t ;

/* Variables and functions */
 int O_CLOEXEC_ ; 
 int /*<<< orphan*/  STRACE (char*,int) ; 
 int /*<<< orphan*/  _EINVAL ; 
 int /*<<< orphan*/  _ENOMEM ; 
 struct fd* adhoc_fd_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  epoll_ops ; 
 int /*<<< orphan*/  f_install (struct fd*,int) ; 
 int /*<<< orphan*/  poll_create () ; 

fd_t sys_epoll_create(int_t flags) {
    STRACE("epoll_create(%#x)", flags);
    if (flags & ~(O_CLOEXEC_))
        return _EINVAL;

    struct fd *fd = adhoc_fd_create(&epoll_ops);
    if (fd == NULL)
        return _ENOMEM;
    fd->epollfd.poll = poll_create();
    return f_install(fd, flags);
}