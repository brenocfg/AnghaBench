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
struct sockaddr_max_ {int dummy; } ;
struct fd {int /*<<< orphan*/  real_fd; } ;
typedef  scalar_t__ ssize_t ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,char*,int,int,scalar_t__,int) ; 
 int _EBADF ; 
 int _EFAULT ; 
 int _EINVAL ; 
 int errno_map () ; 
 scalar_t__ sendto (int /*<<< orphan*/ ,char*,int,int,void*,int) ; 
 int sock_flags_to_real (int) ; 
 struct fd* sock_getfd (int /*<<< orphan*/ ) ; 
 int sockaddr_read (scalar_t__,struct sockaddr_max_*,int*) ; 
 scalar_t__ user_read (scalar_t__,char*,int) ; 

int_t sys_sendto(fd_t sock_fd, addr_t buffer_addr, dword_t len, dword_t flags, addr_t sockaddr_addr, dword_t sockaddr_len) {
    struct fd *sock = sock_getfd(sock_fd);
    if (sock == NULL)
        return _EBADF;
    char buffer[len + 1];
    if (user_read(buffer_addr, buffer, len))
        return _EFAULT;
    buffer[len] = '\0';
    STRACE("sendto(%d, \"%.100s\", %d, %d, 0x%x, %d)", sock_fd, buffer, len, flags, sockaddr_addr, sockaddr_len);
    int real_flags = sock_flags_to_real(flags);
    if (real_flags < 0)
        return _EINVAL;
    struct sockaddr_max_ sockaddr;
    if (sockaddr_addr) {
        int err = sockaddr_read(sockaddr_addr, &sockaddr, &sockaddr_len);
        if (err < 0)
            return err;
    }

    ssize_t res = sendto(sock->real_fd, buffer, len, real_flags,
            sockaddr_addr ? (void *) &sockaddr : NULL, sockaddr_len);
    if (res < 0)
        return errno_map();
    return res;
}