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
struct TYPE_2__ {scalar_t__ domain; int /*<<< orphan*/  unix_got_peer; int /*<<< orphan*/ * unix_peer; int /*<<< orphan*/  unix_cred; } ;
struct fd {TYPE_1__ socket; int /*<<< orphan*/  real_fd; } ;
typedef  int ssize_t ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 scalar_t__ AF_LOCAL_ ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _EBADF ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int connect (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int errno_map () ; 
 int /*<<< orphan*/  fill_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_lock ; 
 struct fd* sock_getfd (int /*<<< orphan*/ ) ; 
 int sockaddr_read (int /*<<< orphan*/ ,struct sockaddr_max_*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int write (int /*<<< orphan*/ ,struct fd**,int) ; 

int_t sys_connect(fd_t sock_fd, addr_t sockaddr_addr, uint_t sockaddr_len) {
    STRACE("connect(%d, 0x%x, %d)", sock_fd, sockaddr_addr, sockaddr_len);
    struct fd *sock = sock_getfd(sock_fd);
    if (sock == NULL)
        return _EBADF;
    struct sockaddr_max_ sockaddr;
    int err = sockaddr_read(sockaddr_addr, &sockaddr, &sockaddr_len);
    if (err < 0)
        return err;

    err = connect(sock->real_fd, (void *) &sockaddr, sockaddr_len);
    if (err < 0)
        return errno_map();

    if (sock->socket.domain == AF_LOCAL_) {
        fill_cred(&sock->socket.unix_cred);
        assert(sock->socket.unix_peer == NULL);
        // Send a pointer to ourselves to the other end so they can set up the peer pointers.
        ssize_t res = write(sock->real_fd, &sock, sizeof(struct fd *));
        if (res == sizeof(struct fd *)) {
            // Wait for acknowledgement that it happened.
            lock(&peer_lock);
            while (sock->socket.unix_peer == NULL)
                wait_for(&sock->socket.unix_got_peer, &peer_lock, NULL);
            unlock(&peer_lock);
        }
    }

    return err;
}