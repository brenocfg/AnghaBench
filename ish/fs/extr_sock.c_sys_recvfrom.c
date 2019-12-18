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
typedef  int uint_t ;
struct fd {int /*<<< orphan*/  real_fd; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  sockaddr ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,scalar_t__,int,int,scalar_t__,scalar_t__) ; 
 int _EBADF ; 
 int _EFAULT ; 
 int _EINVAL ; 
 int errno_map () ; 
 scalar_t__ recvfrom (int /*<<< orphan*/ ,char*,int,int,void*,int*) ; 
 int sock_flags_to_real (int) ; 
 struct fd* sock_getfd (int /*<<< orphan*/ ) ; 
 int sockaddr_write (scalar_t__,char*,int,int*) ; 
 scalar_t__ user_get (scalar_t__,int) ; 
 scalar_t__ user_put (scalar_t__,int) ; 
 scalar_t__ user_write (scalar_t__,char*,int) ; 

int_t sys_recvfrom(fd_t sock_fd, addr_t buffer_addr, dword_t len, dword_t flags, addr_t sockaddr_addr, addr_t sockaddr_len_addr) {
    STRACE("recvfrom(%d, 0x%x, %d, %d, 0x%x, 0x%x)", sock_fd, buffer_addr, len, flags, sockaddr_addr, sockaddr_len_addr);
    struct fd *sock = sock_getfd(sock_fd);
    if (sock == NULL)
        return _EBADF;
    int real_flags = sock_flags_to_real(flags);
    if (real_flags < 0)
        return _EINVAL;
    uint_t sockaddr_len = 0;
    if (sockaddr_len_addr != 0)
        if (user_get(sockaddr_len_addr, sockaddr_len))
            return _EFAULT;

    char buffer[len];
    char sockaddr[sockaddr_len];
    ssize_t res = recvfrom(sock->real_fd, buffer, len, real_flags,
            sockaddr_addr != 0 ? (void *) sockaddr : NULL,
            sockaddr_len_addr != 0 ? &sockaddr_len : NULL);
    if (res < 0)
        return errno_map();

    if (user_write(buffer_addr, buffer, len))
        return _EFAULT;
    if (sockaddr_addr != 0) {
        int err = sockaddr_write(sockaddr_addr, sockaddr, sizeof(sockaddr), &sockaddr_len);
        if (err < 0)
            return err;
    }
    if (sockaddr_len_addr != 0)
        if (user_put(sockaddr_len_addr, sockaddr_len))
            return _EFAULT;
    return res;
}