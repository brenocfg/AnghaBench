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
typedef  int /*<<< orphan*/  uint_t ;
struct sockaddr_max_ {int dummy; } ;
struct inode_data {int dummy; } ;
struct TYPE_2__ {struct inode_data* unix_name_inode; int /*<<< orphan*/ * unix_name_abstract; } ;
struct fd {TYPE_1__ socket; int /*<<< orphan*/  real_fd; } ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _EBADF ; 
 int bind (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int errno_map () ; 
 int /*<<< orphan*/  inode_release_if_exist (struct inode_data*) ; 
 struct fd* sock_getfd (int /*<<< orphan*/ ) ; 
 int sockaddr_read_bind (int /*<<< orphan*/ ,struct sockaddr_max_*,int /*<<< orphan*/ *,struct fd*) ; 
 int /*<<< orphan*/  unix_abstract_release (int /*<<< orphan*/ *) ; 

int_t sys_bind(fd_t sock_fd, addr_t sockaddr_addr, uint_t sockaddr_len) {
    STRACE("bind(%d, 0x%x, %d)", sock_fd, sockaddr_addr, sockaddr_len);
    struct fd *sock = sock_getfd(sock_fd);
    if (sock == NULL)
        return _EBADF;
    struct sockaddr_max_ sockaddr;
    struct inode_data *inode = NULL;
    int err = sockaddr_read_bind(sockaddr_addr, &sockaddr, &sockaddr_len, sock);
    if (err < 0)
        return err;

    err = bind(sock->real_fd, (void *) &sockaddr, sockaddr_len);
    if (err < 0) {
        inode_release_if_exist(sock->socket.unix_name_inode);
        if (sock->socket.unix_name_abstract != NULL)
            unix_abstract_release(sock->socket.unix_name_abstract);
        return errno_map();
    }
    sock->socket.unix_name_inode = inode;
    return 0;
}