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
struct TYPE_2__ {scalar_t__ domain; int /*<<< orphan*/  unix_got_peer; struct fd* unix_peer; int /*<<< orphan*/  unix_cred; int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; } ;
struct fd {TYPE_1__ socket; int /*<<< orphan*/  real_fd; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sockaddr ;
typedef  int /*<<< orphan*/  peer ;
typedef  int int_t ;
typedef  scalar_t__ fd_t ;
typedef  int dword_t ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 scalar_t__ AF_LOCAL_ ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  STRACE (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int _EBADF ; 
 int _EFAULT ; 
 int accept (int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int errno_map () ; 
 struct fd* f_get (scalar_t__) ; 
 int /*<<< orphan*/  fill_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_lock ; 
 int read (int,struct fd**,int) ; 
 scalar_t__ sock_fd_create (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fd* sock_getfd (scalar_t__) ; 
 int sockaddr_write (scalar_t__,char*,int,int*) ; 
 int /*<<< orphan*/  sockrestart_begin_listen_wait (struct fd*) ; 
 int /*<<< orphan*/  sockrestart_end_listen_wait (struct fd*) ; 
 scalar_t__ sockrestart_should_restart_listen_wait () ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_get (scalar_t__,int) ; 
 scalar_t__ user_put (scalar_t__,int) ; 

int_t sys_accept(fd_t sock_fd, addr_t sockaddr_addr, addr_t sockaddr_len_addr) {
    STRACE("accept(%d, 0x%x, 0x%x)", sock_fd, sockaddr_addr, sockaddr_len_addr);
    struct fd *sock = sock_getfd(sock_fd);
    if (sock == NULL)
        return _EBADF;
    dword_t sockaddr_len = 0;
    if (sockaddr_addr != 0) {
        if (user_get(sockaddr_len_addr, sockaddr_len))
            return _EFAULT;
    }

    char sockaddr[sockaddr_len];
    int client;
    do {
        sockrestart_begin_listen_wait(sock);
        errno = 0;
        client = accept(sock->real_fd,
                sockaddr_addr != 0 ? (void *) sockaddr : NULL,
                sockaddr_addr != 0 ? &sockaddr_len : NULL);
        sockrestart_end_listen_wait(sock);
    } while (sockrestart_should_restart_listen_wait() && errno == EINTR);
    if (client < 0)
        return errno_map();

    if (sockaddr_addr != 0) {
        int err = sockaddr_write(sockaddr_addr, sockaddr, sizeof(sockaddr), &sockaddr_len);
        if (err < 0)
            return client;
        if (user_put(sockaddr_len_addr, sockaddr_len))
            return _EFAULT;
    }

    fd_t client_f = sock_fd_create(client,
            sock->socket.domain, sock->socket.type, sock->socket.protocol);
    if (client_f < 0)
        close(client);

    if (sock->socket.domain == AF_LOCAL_) {
        lock(&peer_lock);
        struct fd *client_fd = f_get(client_f);
        fill_cred(&client_fd->socket.unix_cred);
        struct fd *peer;
        ssize_t res = read(client, &peer, sizeof(peer));
        if (res == sizeof(peer)) {
            client_fd->socket.unix_peer = peer;
            peer->socket.unix_peer = client_fd;
            notify(&peer->socket.unix_got_peer);
        }
        unlock(&peer_lock);
    }

    return client_f;
}