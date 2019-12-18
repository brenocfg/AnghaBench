#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ucred_ {int uid; int gid; scalar_t__ pid; } ;
struct TYPE_6__ {int domain; int type; int protocol; TYPE_2__* unix_peer; } ;
struct fd {int /*<<< orphan*/  real_fd; TYPE_3__ socket; } ;
typedef  int /*<<< orphan*/  int_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_4__ {struct ucred_ unix_cred; } ;
struct TYPE_5__ {TYPE_1__ socket; } ;

/* Variables and functions */
 scalar_t__ AF_LOCAL_ ; 
 int SOL_SOCKET_ ; 
 int SO_DOMAIN_ ; 
 int SO_PEERCRED_ ; 
 int SO_PROTOCOL_ ; 
 int SO_TYPE_ ; 
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _EBADF ; 
 int /*<<< orphan*/  _EFAULT ; 
 int /*<<< orphan*/  _EINVAL ; 
 int /*<<< orphan*/  errno_map () ; 
 int getsockopt (int /*<<< orphan*/ ,int,int,char*,int*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  peer_lock ; 
 struct fd* sock_getfd (int /*<<< orphan*/ ) ; 
 int sock_level_to_real (int) ; 
 int sock_opt_to_real (int,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_get (int,int) ; 
 scalar_t__ user_put (int,...) ; 
 scalar_t__ user_read (int /*<<< orphan*/ ,char*,int) ; 

int_t sys_getsockopt(fd_t sock_fd, dword_t level, dword_t option, addr_t value_addr, dword_t len_addr) {
    STRACE("getsockopt(%d, %d, %d, %#x, %#x)", sock_fd, level, option, value_addr, len_addr);
    struct fd *sock = sock_getfd(sock_fd);
    if (sock == NULL)
        return _EBADF;
    dword_t value_len;
    if (user_get(len_addr, value_len))
        return _EFAULT;
    char value[value_len];
    if (user_read(value_addr, value, value_len))
        return _EFAULT;

    if (level == SOL_SOCKET_ && (option == SO_DOMAIN_ || option == SO_TYPE_ || option == SO_PROTOCOL_)) {
        dword_t *value_p = (dword_t *) value;
        if (value_len != sizeof(*value_p))
            return _EINVAL;
        if (option == SO_DOMAIN_)
            *value_p = sock->socket.domain;
        else if (option == SO_TYPE_)
            *value_p = sock->socket.type;
        else if (option == SO_PROTOCOL_)
            *value_p = sock->socket.protocol;
    } else if (level == SOL_SOCKET_ && option == SO_PEERCRED_) {
        struct ucred_ *cred = (struct ucred_ *) value;
        if (value_len != sizeof(*cred))
            return _EINVAL;
        lock(&peer_lock);
        if (sock->socket.domain != AF_LOCAL_ || sock->socket.unix_peer == NULL) {
            cred->pid = 0;
            cred->uid = cred->gid = -1;
        } else {
            *cred = sock->socket.unix_peer->socket.unix_cred;
        }
        unlock(&peer_lock);
    } else {
        int real_opt = sock_opt_to_real(option, level);
        if (real_opt < 0)
            return _EINVAL;
        int real_level = sock_level_to_real(level);
        if (real_level < 0)
            return _EINVAL;

        int err = getsockopt(sock->real_fd, real_level, real_opt, value, &value_len);
        if (err < 0)
            return errno_map();
    }

    if (user_put(len_addr, value_len))
        return _EFAULT;
    if (user_put(value_addr, value))
        return _EFAULT;
    return 0;
}