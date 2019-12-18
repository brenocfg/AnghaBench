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
struct fd {int /*<<< orphan*/  real_fd; } ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int) ; 
 int _EBADF ; 
 int errno_map () ; 
 int listen (int /*<<< orphan*/ ,int) ; 
 struct fd* sock_getfd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockrestart_begin_listen (struct fd*) ; 

int_t sys_listen(fd_t sock_fd, int_t backlog) {
    STRACE("listen(%d, %d)", sock_fd, backlog);
    struct fd *sock = sock_getfd(sock_fd);
    if (sock == NULL)
        return _EBADF;
    int err = listen(sock->real_fd, backlog);
    if (err < 0)
        return errno_map();
    sockrestart_begin_listen(sock);
    return err;
}